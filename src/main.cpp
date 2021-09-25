#include <SDL.h>
#include <SDL_keyboard.h>
#include <SDL_mixer.h>
#include <iomanip>
#include <list>
#include <math.h>
#include <memory>
#include <sstream>

#include <boost/di.hpp>

#include "./util/pair-operators.hpp"
#include "config/configuration.hpp"
#include "debug/debug-overlay.hpp"
#include "input/direction-input-helpers.hpp"
#include "map-generator/deterministic-prng.hpp"
#include "map/camera.hpp"
#include "map/isometric-tile-map-sector.hpp"
#include "map/map-sector-database-hashmap-impl.hpp"
#include "map/map-sector-database.hpp"
#include "map/screen-coordinate-mapper.hpp"
#include "map/sector-spatial-utils.hpp"
#include "map/world-to-map-sector-index.hpp"
#include "player/player.hpp"
#include "render/sdl-manager.hpp"
#include "sprites/sprite-metadata.hpp"
#include "sprites/sprite-registry.hpp"
#include "sprites/sprite-selector.hpp"
#include "sprites/sprite-state.hpp"
#include "sprites/sprite.hpp"

namespace di = boost::di;

#define PI 3.14159265
#define ISOMETRIC_ANGLE = 29.9

float degreesToRadians(float degrees) {
  const float radianUnit = 180.0;
  return degrees * PI / radianUnit;
}

float calculateHorizontalVectorComponent(float vectorMagnitude) {
  const float angle = 26.6;
  return vectorMagnitude * cos(degreesToRadians(angle));
}

float calculateVerticalVectorComponent(float vectorMagnitude) {
  const float angle = 26.6;
  return vectorMagnitude * sin(degreesToRadians(angle));
}

int main() {
  // BEGIN: SDL Setup area
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  int audioFlags = MIX_INIT_MP3 | MIX_INIT_MOD;
  int audioInitState = Mix_Init(audioFlags);
  if (audioInitState & !audioFlags) {
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
      di::bind<Camera>().to<Camera>().in(di::singleton),
      di::bind<SpriteRegistry>().to<SpriteRegistry>().in(di::singleton),
      di::bind<DeterministicPrng>().to<DeterministicPrng>().in(di::singleton),
      di::bind<Configuration>().to<Configuration>().in(di::singleton),
      di::bind<MapSectorDatabase>().to<MapSectorDatabaseHashmapImpl>().in(
          di::singleton));

  auto sdlManager = injector.create<std::shared_ptr<SDLManager>>();
  auto camera = injector.create<std::shared_ptr<Camera>>();
  auto debugOverlay = injector.create<DebugOverlay>();
  auto screenCoordinateMapper = injector.create<ScreenCoordinateMapper>();
  auto textRenderer = injector.create<TextRenderer>();
  auto configuration = injector.create<std::shared_ptr<Configuration>>();
  auto mapSectorDatabase =
      injector.create<std::shared_ptr<MapSectorDatabase>>();
  // END: SDL Setup area

  // BEGIN: Audio Setup area
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
    exit(2);
  }

  Mix_Chunk *gameMusic;
  gameMusic = Mix_LoadWAV("./assets/x109.wav");
  if (gameMusic == 0) {
    printf("Mix_LoadWAV: %s\n", Mix_GetError());
    // handle error
  }

  // TODO: Put this in config.
  bool playMusic = true;
  if (playMusic) {
    if (Mix_PlayChannel(-1, gameMusic, 0) == -1) {
      printf("Mix_PlayMusic: %s\n", Mix_GetError());
      // well, there's no music, but most games don't break without music...
    }
  }
  // END: Audio Setup area

  // BEGIN: Asset loading

  auto playerSpriteSelector = injector.create<SpriteSelector>();
  auto spriteRegistry = injector.create<std::shared_ptr<SpriteRegistry>>();
  auto prng = injector.create<std::shared_ptr<DeterministicPrng>>();
  auto player = injector.create<Player>();
  try {
    struct SpriteMetadata playerSpriteMetadata = {.rows = 4, .columns = 4};

    spriteRegistry->loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot225.png",
        "tank_idle_rot225", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        North, spriteRegistry->getSprite("tank_idle_rot225"));

    spriteRegistry->loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot180.png",
        "tank_idle_rot180", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        NorthEast, spriteRegistry->getSprite("tank_idle_rot180"));

    spriteRegistry->loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot135.png",
        "tank_idle_rot135", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        East, spriteRegistry->getSprite("tank_idle_rot135"));

    spriteRegistry->loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot090.png",
        "tank_idle_rot090", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        SouthEast, spriteRegistry->getSprite("tank_idle_rot090"));

    spriteRegistry->loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot045.png",
        "tank_idle_rot045", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        South, spriteRegistry->getSprite("tank_idle_rot045"));

    spriteRegistry->loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot000.png",
        "tank_idle_rot000", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        SouthWest, spriteRegistry->getSprite("tank_idle_rot000"));

    spriteRegistry->loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot315.png",
        "tank_idle_rot315", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        West, spriteRegistry->getSprite("tank_idle_rot315"));

    spriteRegistry->loadSprite(
        "./assets/Rendered spritesheets/tank_idle_rot270.png",
        "tank_idle_rot270", &playerSpriteMetadata);
    playerSpriteSelector.registerDirectionSprite(
        NorthWest, spriteRegistry->getSprite("tank_idle_rot270"));

    player.setSpriteSelector(playerSpriteSelector);
    struct SpriteMetadata tileSpriteMetadata = {.rows = 3, .columns = 10};

    spriteRegistry->loadSprite("./assets/desert_tile_0_sheet.png", "0",
                               &tileSpriteMetadata);
    spriteRegistry->loadSprite("./assets/desert_tile_0_sheet.png", "1",
                               &tileSpriteMetadata);
    spriteRegistry->loadSprite("./assets/water_tile_0_sheet.png", "2",
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
  auto sectorSpatialUtils = injector.create<SectorSpatialUtils>();
  auto worldToMapSectorIndex = injector.create<WorldToMapSectorIndex>();

  SpriteState spriteState = {.direction = North};

  camera->setTarget(&player);
  /* Game loop */
  long int lastFrameTicks = SDL_GetTicks();
  bool running = true;
  while (running) {
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
          running = false;
        case SDLK_F12:
          configuration->setIsDebugMode(!configuration->getIsDebugMode());
          break;
        }
        break;
      case SDL_MOUSEWHEEL:
        if (event.wheel.y > 0) {
          camera->setZoom(camera->getZoom() + 0.25f);
        } else if (event.wheel.y < 0) {
          camera->setZoom(camera->getZoom() - 0.25f);
        }
        break;
      }
    }

    const int speed = 400;
    /* Read and process input control keys */
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (!DirectionInputHelpers::noKeysPressed(keyState)) {
      spriteState.direction =
          DirectionInputHelpers::getInputDirection(keyState);

      switch (spriteState.direction) {
      case NorthWest:
        player.setVelocity(
            std::make_pair(-calculateHorizontalVectorComponent(speed),
                           -calculateVerticalVectorComponent(-speed)));
        break;
      case NorthEast:
        player.setVelocity(
            std::make_pair(+calculateHorizontalVectorComponent(speed),
                           -calculateVerticalVectorComponent(-speed)));
        break;
      case SouthEast:
        player.setVelocity(
            std::make_pair(+calculateHorizontalVectorComponent(speed),
                           -calculateVerticalVectorComponent(speed)));
        break;
      case SouthWest:
        player.setVelocity(
            std::make_pair(-calculateHorizontalVectorComponent(speed),
                           -calculateVerticalVectorComponent(speed)));
        break;
      case South:
        player.setVelocity(std::make_pair(0, -speed));
        break;
      case North:
        player.setVelocity(std::make_pair(0, +speed));
        break;
      case East:
        player.setVelocity(std::make_pair(+speed, 0));
        break;
      case West:
        player.setVelocity(std::make_pair(-speed, 0));
        break;
      case Idle:
        player.setVelocity(std::make_pair(0, 0));
        break;
      }
    } else {
      player.setVelocity(std::make_pair(0, 0));
    }
    long int tickInterval = SDL_GetTicks() - lastFrameTicks;
    player.update(tickInterval);
    camera->update(tickInterval);
    lastFrameTicks = SDL_GetTicks();

    sdlManager->renderClear();

    /* Render / dynamically generate map sectors */
    auto neighbours = sectorSpatialUtils.getNeighbours(
        worldToMapSectorIndex.getMapIndex(player.getPosition()),
        1 / camera->getZoom());

    neighbours.push_back(
        worldToMapSectorIndex.getMapIndex(player.getPosition()));

    SDL_RenderSetScale(sdlManager->getRenderer(), camera->getZoom(),
                       camera->getZoom());
    for (std::list<std::pair<int, int>>::iterator it = neighbours.begin();
         it != neighbours.end(); ++it) {
      auto sectorId = sectorSpatialUtils.fromIntegerPairToKey(*it);
      auto sector = mapSectorDatabase->get(sectorId);

      if (sector != nullptr) {
        sector->render(configuration->getWindowDimensions());
      } else {
        auto sectorId = sectorSpatialUtils.fromIntegerPairToKey(*it);
        mapSectorDatabase->put(
            sectorId,
            std::make_shared<IsometricTileMapSector>(
                sdlManager, camera, spriteRegistry, screenCoordinateMapper,
                textRenderer,
                std::make_pair(
                    it->first * configuration->getSectorDimensions().first,
                    -it->second * configuration->getSectorDimensions()
                                      .second), // BOTTOM LEFT.
                gameSaveState, prng, configuration));
      }
    }

    /* Render player sprite with SpriteSheet */
    player.render(spriteState);

    SDL_RenderSetScale(sdlManager->getRenderer(), 1, 1);
    debugOverlay.render(tickInterval);

    /* redraw */
    SDL_SetRenderDrawColor(sdlManager->getRenderer(), 0, 0, 0, 255);
    SDL_RenderPresent(sdlManager->getRenderer());
  }

  std::cout << "EXIT (return 0)" << std::endl;
  return 0;
}