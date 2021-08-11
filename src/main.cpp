#include <SDL.h>
#include <SDL_keyboard.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iomanip>
#include <math.h>
#include <sstream>

#include "input/direction-input-helpers.hpp"
#include "map/isometric-tile-map-sector.hpp"
#include "sprites/sprite-selector.hpp"
#include "sprites/sprite-state.hpp"
#include "sprites/sprite.hpp"
#include "sprites/sprite-metadata.hpp"
#include "sprites/sprite-registry.hpp"

#define PI 3.14159265

float calculateHorizontalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * cos(26.6 * PI / 180.0);
}

float calculateVerticalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * sin(26.6 * PI / 180.0);
}

std::pair<float, float>
worldToScreen(std::pair<float, float> worldPosition,
              std::pair<int, int> screenDimensions,
              std::pair<float, float> playerSpriteDimensions) {
  return std::make_pair<float, float>(
      -worldPosition.first + (screenDimensions.first / 2) -
          (playerSpriteDimensions.first / 2),
      worldPosition.second + (screenDimensions.second / 2) -
          (playerSpriteDimensions.second / 2));
}

std::pair<float, float> addPair(std::pair<float, float> first,
                                std::pair<float, float> second) {
  return std::make_pair(first.first + second.first,
                        first.second - second.second);
}

int main() {
  std::pair<int, int> screenDimensions(800, 600);

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

  SDL_Window *screen = SDL_CreateWindow(
      "SDL2Application4 (isometric demo)", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, screenDimensions.first, screenDimensions.second,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  SDL_Renderer *gameRenderer =
      SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

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

  SpriteSelector *playerSpriteSelector = new SpriteSelector();
  SpriteRegistry *spriteRegistry = new SpriteRegistry(gameRenderer);
  try {
    struct SpriteMetadata playerSpriteMetadata = { .rows=4, .columns=4 };

    spriteRegistry->loadSprite("./assets/Rendered spritesheets/tank_idle_rot225.png", "tank_idle_rot225", &playerSpriteMetadata);
    playerSpriteSelector->registerDirectionSprite(North, spriteRegistry->getSprite("tank_idle_rot225"));

    spriteRegistry->loadSprite("./assets/Rendered spritesheets/tank_idle_rot180.png", "tank_idle_rot180", &playerSpriteMetadata);
    playerSpriteSelector->registerDirectionSprite(NorthEast, spriteRegistry->getSprite("tank_idle_rot180"));

    spriteRegistry->loadSprite("./assets/Rendered spritesheets/tank_idle_rot135.png", "tank_idle_rot135", &playerSpriteMetadata);
    playerSpriteSelector->registerDirectionSprite(East, spriteRegistry->getSprite("tank_idle_rot135"));

    spriteRegistry->loadSprite("./assets/Rendered spritesheets/tank_idle_rot090.png", "tank_idle_rot090", &playerSpriteMetadata);
    playerSpriteSelector->registerDirectionSprite(SouthEast, spriteRegistry->getSprite("tank_idle_rot090"));

    spriteRegistry->loadSprite("./assets/Rendered spritesheets/tank_idle_rot045.png", "tank_idle_rot045", &playerSpriteMetadata);
    playerSpriteSelector->registerDirectionSprite(South, spriteRegistry->getSprite("tank_idle_rot045"));

    spriteRegistry->loadSprite("./assets/Rendered spritesheets/tank_idle_rot000.png", "tank_idle_rot000", &playerSpriteMetadata);
    playerSpriteSelector->registerDirectionSprite(SouthWest, spriteRegistry->getSprite("tank_idle_rot000"));

    spriteRegistry->loadSprite("./assets/Rendered spritesheets/tank_idle_rot315.png", "tank_idle_rot315", &playerSpriteMetadata);
    playerSpriteSelector->registerDirectionSprite(West, spriteRegistry->getSprite("tank_idle_rot315"));

    spriteRegistry->loadSprite("./assets/Rendered spritesheets/tank_idle_rot270.png", "tank_idle_rot270", &playerSpriteMetadata);
    playerSpriteSelector->registerDirectionSprite(NorthWest, spriteRegistry->getSprite("tank_idle_rot270"));

    struct SpriteMetadata tileSpriteMetadata = { .rows=3, .columns=10 };

    spriteRegistry->loadSprite("./assets/water_tile_2_sheet.png", "0", &tileSpriteMetadata);
    spriteRegistry->loadSprite("./assets/water_tile_1_sheet.png", "1", &tileSpriteMetadata);

  } catch (const std::runtime_error &ex) {
    throw;
  }
  // END: Asset loading

  // BEGIN: Constant setup and state init
  IsometricTileMapSector *isoMapSector = new IsometricTileMapSector(
      spriteRegistry,
      std::make_pair(0.0, 0.0), screenDimensions,
      std::make_pair(spriteRegistry->getSprite("1")->getFrameWidth(),
                     spriteRegistry->getSprite("1")->getFrameHeight()));

  std::pair<float, float> cameraPosition = std::make_pair(0, 0);

  SDL_FRect playerPositioningRect = {
      .x = worldToScreen(cameraPosition, screenDimensions,
                         std::make_pair(spriteRegistry->getSprite("tank_idle_rot225")->getFrameWidth(),
                                        spriteRegistry->getSprite("tank_idle_rot225")->getFrameHeight()))
               .first,
      .y = worldToScreen(cameraPosition, screenDimensions,
                         std::make_pair(spriteRegistry->getSprite("tank_idle_rot225")->getFrameWidth(),
                                        spriteRegistry->getSprite("tank_idle_rot225")->getFrameHeight()))
               .second,
      .w = spriteRegistry->getSprite("tank_idle_rot225")->getFrameWidth(),
      .h = spriteRegistry->getSprite("tank_idle_rot225")->getFrameHeight()};
  SpriteState spriteState = {.direction = North};

  // END: Constant setup and state init

  /* Game loop */
  while (true) {
    
    std::cout << "ABS:" << cameraPosition.first << " " << cameraPosition.second
              << std::endl;
    std::cout << (isoMapSector->pointIntersects(cameraPosition) || isoMapSector->pointIntersects(addPair(cameraPosition, std::make_pair<float, float>(spriteRegistry->getSprite("tank_idle_rot225")->getFrameWidth(), -spriteRegistry->getSprite("tank_idle_rot225")->getFrameHeight())))) << std::endl;
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
        cameraPosition.first -= calculateHorizontalVectorComponent(speed);
        cameraPosition.second -= calculateVerticalVectorComponent(-speed);
        break;
      case NorthEast:
        cameraPosition.first += calculateHorizontalVectorComponent(speed);
        cameraPosition.second -= calculateVerticalVectorComponent(-speed);
        break;
      case SouthEast:
        cameraPosition.first += calculateHorizontalVectorComponent(speed);
        cameraPosition.second -= calculateVerticalVectorComponent(speed);
        break;
      case SouthWest:
        cameraPosition.first -= calculateHorizontalVectorComponent(speed);
        cameraPosition.second -= calculateVerticalVectorComponent(speed);
        break;
      case South:
        cameraPosition.second -= speed;
        break;
      case North:
        cameraPosition.second += speed;
        break;
      case East:
        cameraPosition.first += speed;
        break;
      case West:
        cameraPosition.first -= speed;
        break;
      }
    }

    SDL_RenderClear(gameRenderer);

    std::pair<float, float> isoBottomLeft = isoMapSector->getBottomLeft();
    std::pair<float, float> dim = isoMapSector->getDimensions();
    std::pair<float, float> isoBottomLeftCent =
        addPair(worldToScreen(cameraPosition, screenDimensions,
                              std::make_pair(spriteRegistry->getSprite("tank_idle_rot225")->getFrameWidth(),
                                             spriteRegistry->getSprite("tank_idle_rot225")->getFrameHeight())),
                isoBottomLeft);

    SDL_Rect rectangleRect = {
        .x = isoBottomLeftCent.first,
        .y = isoBottomLeftCent.second,
        .w = dim.first,
        .h = -dim.second,
    };

    /* Lay tiles with SpriteSheet */
    SDL_FRect tilePositionRect = {
        .x = 0,
        .y = worldToScreen(cameraPosition, screenDimensions,
                           std::make_pair(spriteRegistry->getSprite("1")->getFrameWidth(),
                                          spriteRegistry->getSprite("1")->getFrameHeight()))
                 .second,
        .w = spriteRegistry->getSprite("1")->getFrameWidth(),
        .h = spriteRegistry->getSprite("1")->getFrameHeight()};

    for (int y = 0; y < isoMapSector->getTilesPerAxis().second; ++y) {
      for (int x = 0; x < isoMapSector->getTilesPerAxis().first; ++x) {
        if (y % 2 == 0) {
          tilePositionRect.x = isoBottomLeftCent.first +
                               (x * spriteRegistry->getSprite("1")->getFrameWidth());
        } else {
          // Every other row has a negative offset of half the tile width.
          tilePositionRect.x = isoBottomLeftCent.first +
                               (x * spriteRegistry->getSprite("1")->getFrameWidth()) +
                               (spriteRegistry->getSprite("1")->getFrameWidth() / 2);
        }

        if (isoMapSector->getTile(x, y) == 0) {
          spriteRegistry->getSprite("1")->renderTick(&tilePositionRect);
        } else {
          spriteRegistry->getSprite("0")->renderTick(&tilePositionRect);
        }
      }
      tilePositionRect.y -= (spriteRegistry->getSprite("1")->getFrameHeight() / 2);
    }

    /* Render player sprite with SpriteSheet */
    Sprite *playerSprite = playerSpriteSelector->selectSprite(spriteState);
    if (playerSprite != NULL) {
      playerSprite->renderTick(&playerPositioningRect);
    }

    SDL_SetRenderDrawColor(gameRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(gameRenderer, &rectangleRect);

    std::pair<float, float> playerPosition =
        worldToScreen(cameraPosition, screenDimensions,
                      std::make_pair(spriteRegistry->getSprite("tank_idle_rot225")->getFrameWidth(),
                                     spriteRegistry->getSprite("tank_idle_rot225")->getFrameHeight()));
    SDL_Rect playerRect = {
        .x = playerPositioningRect.x,
        .y = playerPositioningRect.y,
        .w = playerPositioningRect.w,
        .h = -playerPositioningRect.h,
    };

    SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gameRenderer, &playerRect);

    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);

    SDL_RenderPresent(gameRenderer);
    SDL_Delay(10);
  }

  return 0;
}