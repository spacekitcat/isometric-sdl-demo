#include <SDL.h>
#include <SDL_keyboard.h>
#include <SDL_mixer.h>
#include <iomanip>
#include <math.h>
#include <sstream>

#include <boost/di.hpp>

#include "./util/pair-operators.hpp"
#include "debug/debug-overlay.hpp"
#include "input/direction-input-helpers.hpp"
#include "map/camera.hpp"
#include "map/coordinate-mapper.hpp"
#include "map/isometric-tile-map-sector.hpp"
#include "render/sdl-manager.hpp"
#include "sprites/sprite-metadata.hpp"
#include "sprites/sprite-registry.hpp"
#include "sprites/sprite-selector.hpp"
#include "sprites/sprite-state.hpp"
#include "sprites/sprite.hpp"
#include "state/game-save-state.hpp"

namespace di = boost::di;

#define PI 3.14159265

float calculateHorizontalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * cos(26.6 * PI / 180.0);
}

float calculateVerticalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * sin(26.6 * PI / 180.0);
}

int main() {
  // BEGIN: SDL Setup area
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  int flags = MIX_INIT_MP3 | MIX_INIT_MOD;
  int initted = Mix_Init(flags);
  if (initted & !flags) {
    printf("Mix_Init: Failed to init required ogg and mod support!\n");
    printf("Mix_Init: %s\n", Mix_GetError());
    return 1;
  }

  if (TTF_Init() != 0) {
    std::cout << "TF_Init: " << TTF_GetError();
    exit(2);
  }

  const auto injector = di::make_injector(
      di::bind<SDLManager>().to<SDLManager>().in(di::singleton),
      di::bind<Camera>().to<Camera>().in(di::singleton));
  auto sdlManager = injector.create<std::shared_ptr<SDLManager>>();
  auto camera = injector.create<std::shared_ptr<Camera>>();
  auto debugOverlay = injector.create<DebugOverlay>();
  auto coordinateMapper = injector.create<CoordinateMapper>();
  auto textRenderer = injector.create<TextRenderer>();
  // END: SDL Setup area

  // BEGIN: Audio Setup area
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
    exit(2);
  }

  Mix_Chunk *sample;
  sample = Mix_LoadWAV("./assets/x109.wav");
  if (!sample) {
    printf("Mix_LoadWAV: %s\n", Mix_GetError());
    // handle error
  }

  // if (Mix_PlayChannel(-1, sample, 0) == -1) {
  //   printf("Mix_PlayMusic: %s\n", Mix_GetError());
  //   // well, there's no music, but most games don't break without music...
  // }
  // END: Audio Setup area

  // BEGIN: Asset loading

  auto playerSpriteSelector = injector.create<SpriteSelector>();
  auto spriteRegistry = injector.create<SpriteRegistry>();
  try {
    struct SpriteMetadata playerSpriteMetadata = {.rows = 4, .columns = 4};

    spriteRegistry.loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot225.png",
        "tank_idle_rot225", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        North, spriteRegistry.getSprite("tank_idle_rot225"));

    spriteRegistry.loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot180.png",
        "tank_idle_rot180", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        NorthEast, spriteRegistry.getSprite("tank_idle_rot180"));

    spriteRegistry.loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot135.png",
        "tank_idle_rot135", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        East, spriteRegistry.getSprite("tank_idle_rot135"));

    spriteRegistry.loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot090.png",
        "tank_idle_rot090", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        SouthEast, spriteRegistry.getSprite("tank_idle_rot090"));

    spriteRegistry.loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot045.png",
        "tank_idle_rot045", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        South, spriteRegistry.getSprite("tank_idle_rot045"));

    spriteRegistry.loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot000.png",
        "tank_idle_rot000", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        SouthWest, spriteRegistry.getSprite("tank_idle_rot000"));

    spriteRegistry.loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot315.png",
        "tank_idle_rot315", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        West, spriteRegistry.getSprite("tank_idle_rot315"));

    spriteRegistry.loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot270.png",
        "tank_idle_rot270", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        NorthWest, spriteRegistry.getSprite("tank_idle_rot270"));

    struct SpriteMetadata tileSpriteMetadata = {.rows = 3, .columns = 10};

    spriteRegistry.loadSprite("./assets/water_tile_2_sheet.png", "0",
                              &tileSpriteMetadata);
    spriteRegistry.loadSprite("./assets/water_tile_1_sheet.png", "1",
                              &tileSpriteMetadata);

  } catch (const std::runtime_error &ex) {
    throw;
  }
  // END: Asset loading

  // TODO: This can't keep changing as it will via DI.
  // I don't want gameSaveState to be a singleton,
  // but it will need some mediator singleton to manage
  // all possible gameState objects.
  auto gameSaveState = injector.create<GameSaveState>();

  // BEGIN: Constant setup and state init
  IsometricTileMapSector *isoMapSector = new IsometricTileMapSector(
      sdlManager, camera, spriteRegistry, coordinateMapper, textRenderer,
      std::make_pair(0.0, 0.0), // TOP LEFT.
      gameSaveState);

  IsometricTileMapSector *isoMapSector2 = new IsometricTileMapSector(
      sdlManager, camera, spriteRegistry, coordinateMapper, textRenderer,
      std::make_pair(0.0,
                     gameSaveState.getSectorDimensions().second), // TOP LEFT.
      gameSaveState);

  SDL_FRect playerPositioningRect = {
      .x = coordinateMapper.centerInScreenSpace(camera->getPosition()).first,
      .y = coordinateMapper.centerInScreenSpace(camera->getPosition()).second,
      .w = spriteRegistry.getSprite("tank_idle_rot225")->getFrameWidth(),
      .h = spriteRegistry.getSprite("tank_idle_rot225")->getFrameHeight()};
  SpriteState spriteState = {.direction = North};
  // END: Constant setup and state init

  /* Game loop */
  while (true) {
    SDL_Event event;

    /* Process events and session control level */
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        return 0;
        break;

      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
          return 0;
          break;
        }
      }
    }

    const int speed = 2;
    /* Read and process input control keys */
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (!DirectionInputHelpers::noKeysPressed(keyState)) {
      spriteState.direction =
          DirectionInputHelpers::getInputDirection(keyState);

      switch (spriteState.direction) {
      case NorthWest:
        camera->applyDelta(
            std::make_pair(-calculateHorizontalVectorComponent(speed),
                           -calculateVerticalVectorComponent(-speed)));
        break;
      case NorthEast:
        camera->applyDelta(
            std::make_pair(+calculateHorizontalVectorComponent(speed),
                           -calculateVerticalVectorComponent(-speed)));
        break;
      case SouthEast:
        camera->applyDelta(
            std::make_pair(+calculateHorizontalVectorComponent(speed),
                           -calculateVerticalVectorComponent(speed)));
        break;
      case SouthWest:
        camera->applyDelta(
            std::make_pair(-calculateHorizontalVectorComponent(speed),
                           -calculateVerticalVectorComponent(speed)));
        break;
      case South:
        camera->applyDelta(std::make_pair(0, -speed));
        break;
      case North:
        camera->applyDelta(std::make_pair(0, +speed));
        break;
      case East:
        camera->applyDelta(std::make_pair(+speed, 0));
        break;
      case West:
        camera->applyDelta(std::make_pair(-speed, 0));
        break;
      case Idle:
        break;
      }
    }

    sdlManager->renderClear();

    Sprite *playerSprite = playerSpriteSelector.selectSprite(spriteState);

    if (isoMapSector->isVisible()) {
      isoMapSector->render(sdlManager->getWindowDimensions());
    }

    if (isoMapSector2->isVisible()) {
      isoMapSector2->render(sdlManager->getWindowDimensions());
    }

    /* Render player sprite with SpriteSheet */
    if (playerSprite != NULL) {
      playerSprite->renderTick(&playerPositioningRect);
    }

    debugOverlay.render();

    /* redraw */
    SDL_SetRenderDrawColor(sdlManager->getRenderer(), 0, 0, 0, 255);
    SDL_RenderPresent(sdlManager->getRenderer());
    SDL_Delay(10);
  }

  return 0;
}