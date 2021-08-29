#include <SDL.h>
#include <SDL_keyboard.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iomanip>
#include <math.h>
#include <sstream>

#include <boost/di.hpp>
#include <boost/format.hpp>

#include "./util/pair-operators.hpp"
#include "debug/debug-draw-utils.hpp"
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

namespace di = boost::di;

#define PI 3.14159265

float calculateHorizontalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * cos(26.6 * PI / 180.0);
}

float calculateVerticalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * sin(26.6 * PI / 180.0);
}

void renderText(TTF_Font *font, std::shared_ptr<SDLManager> sdlManager,
                std::string text) {

  TTF_SetFontOutline(font, 1);
  SDL_Color textBgColor = {0, 0, 0};
  SDL_Surface *text_surface_bg =
      TTF_RenderText_Blended(font, text.c_str(), textBgColor);

  TTF_SetFontOutline(font, 0);
  SDL_Color textFgColor = {255, 255, 255};
  SDL_Surface *text_surface_fg =
      TTF_RenderText_Blended(font, text.c_str(), textFgColor);

  SDL_Rect offset = {.x = 1, .y = 1};
  SDL_BlitSurface(text_surface_fg, NULL, text_surface_bg, &offset);

  SDL_Texture *tex =
      SDL_CreateTextureFromSurface(sdlManager->getRenderer(), text_surface_bg);

  SDL_Rect dest = {
      .x = 100, .y = 25, .w = text_surface_bg->w, .h = text_surface_bg->h};
  SDL_RenderCopy(sdlManager->getRenderer(), tex, NULL, &dest);

  // SDL_DestroyTexture(tex);

  SDL_FreeSurface(text_surface_bg);
  SDL_FreeSurface(text_surface_fg);
}

int main() {
  std::pair<int, int> screenDimensions(1024, 768);

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

  const auto injector = di::make_injector(
      di::bind<SDLManager>().to<SDLManager>().in(di::singleton),
      di::bind<Camera>().to<Camera>().in(di::singleton));
  auto sdlManager = injector.create<std::shared_ptr<SDLManager>>();
  auto camera = injector.create<std::shared_ptr<Camera>>();

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

  // BEGIN: TTF Setup area
  if (TTF_Init() != 0) {
    std::cout << "TF_Init: " << TTF_GetError();
    exit(2);
  }

  TTF_Font *font;
  font = TTF_OpenFont("./assets/fonts/Lato-Bold.ttf", 18);
  // TTF_SetFontOutline(font, 1);

  if (!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    exit(2);
  }

  // SDL_Surface *screen;

  // END: TTF Setup area

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

  // BEGIN: Constant setup and state init
  IsometricTileMapSector *isoMapSector = new IsometricTileMapSector(
      sdlManager, camera, spriteRegistry, std::make_pair(0.0, 0.0),
      screenDimensions,
      std::make_pair(spriteRegistry.getSprite("1")->getFrameWidth(),
                     spriteRegistry.getSprite("1")->getFrameHeight()));

  IsometricTileMapSector *isoMapSector2 = new IsometricTileMapSector(
      sdlManager, camera, spriteRegistry,
      std::make_pair(0.0, screenDimensions.second), screenDimensions,
      std::make_pair(spriteRegistry.getSprite("1")->getFrameWidth(),
                     spriteRegistry.getSprite("1")->getFrameHeight()));

  IsometricTileMapSector *isoMapSector3 = new IsometricTileMapSector(
      sdlManager, camera, spriteRegistry,
      std::make_pair(0.0, -screenDimensions.second), screenDimensions,
      std::make_pair(spriteRegistry.getSprite("1")->getFrameWidth(),
                     spriteRegistry.getSprite("1")->getFrameHeight()));

  IsometricTileMapSector *isoMapSector4 = new IsometricTileMapSector(
      sdlManager, camera, spriteRegistry,
      std::make_pair(screenDimensions.first, 0.0), screenDimensions,
      std::make_pair(spriteRegistry.getSprite("1")->getFrameWidth(),
                     spriteRegistry.getSprite("1")->getFrameHeight()));

  IsometricTileMapSector *isoMapSector5 = new IsometricTileMapSector(
      sdlManager, camera, spriteRegistry,
      std::make_pair(-screenDimensions.first, 0.0), screenDimensions,
      std::make_pair(spriteRegistry.getSprite("1")->getFrameWidth(),
                     spriteRegistry.getSprite("1")->getFrameHeight()));

  SDL_FRect playerPositioningRect = {
      .x =
          CoordinateMapper::worldToScreen(
              camera->getPosition(), screenDimensions,
              std::make_pair(
                  spriteRegistry.getSprite("tank_idle_rot225")->getFrameWidth(),
                  spriteRegistry.getSprite("tank_idle_rot225")
                      ->getFrameHeight()))
              .first,
      .y =
          CoordinateMapper::worldToScreen(
              camera->getPosition(), screenDimensions,
              std::make_pair(
                  spriteRegistry.getSprite("tank_idle_rot225")->getFrameWidth(),
                  spriteRegistry.getSprite("tank_idle_rot225")
                      ->getFrameHeight()))
              .second,
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

    if (isoMapSector->squareIntersects(camera->getPosition(),
                                       screenDimensions)) {
      isoMapSector->render(screenDimensions);
    }

    if (isoMapSector2->squareIntersects(camera->getPosition(),
                                        screenDimensions)) {
      isoMapSector2->render(screenDimensions);
    }

    if (isoMapSector3->squareIntersects(camera->getPosition(),
                                        screenDimensions)) {
      isoMapSector3->render(screenDimensions);
    }

    if (isoMapSector4->squareIntersects(camera->getPosition(),
                                        screenDimensions)) {
      isoMapSector4->render(screenDimensions);
    }

    if (isoMapSector5->squareIntersects(camera->getPosition(),
                                        screenDimensions)) {
      isoMapSector5->render(screenDimensions);
    }

    /* Render player sprite with SpriteSheet */
    Sprite *playerSprite = playerSpriteSelector.selectSprite(spriteState);
    if (playerSprite != NULL) {
      playerSprite->renderTick(&playerPositioningRect);
    }

    SDL_Rect playerRect = {
        .x = playerPositioningRect.x,
        .y = playerPositioningRect.y,
        .w = playerPositioningRect.w,
        .h = -playerPositioningRect.h,
    };

    SDL_SetRenderDrawColor(sdlManager->getRenderer(), 255, 255, 255, 255);
    SDL_RenderDrawRect(sdlManager->getRenderer(), &playerRect);

    SDL_SetRenderDrawColor(sdlManager->getRenderer(), 255, 255, 255, 255);
    renderText(font, sdlManager,
               str(boost::format("%1$+5d %2$+5d") %
                   round(camera->getPosition().first) %
                   round(camera->getPosition().second)));

    /* redraw */
    SDL_SetRenderDrawColor(sdlManager->getRenderer(), 0, 0, 0, 255);
    SDL_RenderPresent(sdlManager->getRenderer());
    SDL_Delay(10);
  }

  return 0;
}