#include <SDL.h>
#include <SDL_keyboard.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iomanip>
#include <math.h>
#include <random>
#include <sstream>

#include "input/direction-input-helpers.hpp"
#include "map/isometric-tile-map-sector.hpp"
#include "sprites/sprite-selector.hpp"
#include "sprites/sprite-state.hpp"
#include "sprites/sprite.hpp"

using namespace std;

#define PI 3.14159265

float calculateHorizontalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * cos(26.6 * PI / 180.0);
}

float calculateVerticalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * sin(26.6 * PI / 180.0);
}

std::pair<float, float> centerCamera(std::pair<float, float> worldPosition, std::pair<int, int> screenDimensions, std::pair<float, float> playerSpriteDimensions) {
  return std::make_pair<float, float>(
      -worldPosition.first + (screenDimensions.first / 2) -
          (playerSpriteDimensions.first / 2),
      worldPosition.second + (screenDimensions.second / 2) -
          (playerSpriteDimensions.second / 2));
}

int main() {
  auto map = new int[512][512];

  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(0, 2);
  for (int i = 0; i < 512; ++i) {
    for (int j = 0; j < 512; ++j) {
      map[i][j] = uniform_dist(e1);
    }
  }

  const int screenWidth = 800;
  const int screenHeight = 600;

  IsometricTileMapSector *isoMapSector = new IsometricTileMapSector(
      std::make_pair(0.0, 0.0), std::make_pair(screenWidth, screenHeight));

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
      SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight,
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

  Sprite *playerSpriteN = NULL;
  Sprite *playerSpriteNE = NULL;
  Sprite *playerSpriteE = NULL;
  Sprite *playerSpriteSE = NULL;
  Sprite *playerSpriteS = NULL;
  Sprite *playerSpriteSW = NULL;
  Sprite *playerSpriteW = NULL;
  Sprite *playerSpriteNW = NULL;

  Sprite *seaTileSpriteSheet = NULL;
  Sprite *seaTileSpriteSheet1 = NULL;
  try {
    playerSpriteN =
        new Sprite(gameRenderer,
                   "./assets/Rendered spritesheets/tank_idle_rot225.png", 4, 4);
    playerSpriteSelector->registerDirectionSprite(North, playerSpriteN);

    playerSpriteNE =
        new Sprite(gameRenderer,
                   "./assets/Rendered spritesheets/tank_idle_rot180.png", 4, 4);
    playerSpriteSelector->registerDirectionSprite(NorthEast, playerSpriteNE);

    playerSpriteE =
        new Sprite(gameRenderer,
                   "./assets/Rendered spritesheets/tank_idle_rot135.png", 4, 4);
    playerSpriteSelector->registerDirectionSprite(East, playerSpriteE);

    playerSpriteSE =
        new Sprite(gameRenderer,
                   "./assets/Rendered spritesheets/tank_idle_rot090.png", 4, 4);
    playerSpriteSelector->registerDirectionSprite(SouthEast, playerSpriteSE);

    playerSpriteS =
        new Sprite(gameRenderer,
                   "./assets/Rendered spritesheets/tank_idle_rot045.png", 4, 4);
    playerSpriteSelector->registerDirectionSprite(South, playerSpriteS);

    playerSpriteSW =
        new Sprite(gameRenderer,
                   "./assets/Rendered spritesheets/tank_idle_rot000.png", 4, 4);
    playerSpriteSelector->registerDirectionSprite(SouthWest, playerSpriteSW);

    playerSpriteW =
        new Sprite(gameRenderer,
                   "./assets/Rendered spritesheets/tank_idle_rot315.png", 4, 4);
    playerSpriteSelector->registerDirectionSprite(West, playerSpriteW);

    playerSpriteNW =
        new Sprite(gameRenderer,
                   "./assets/Rendered spritesheets/tank_idle_rot270.png", 4, 4);
    playerSpriteSelector->registerDirectionSprite(NorthWest, playerSpriteNW);

    seaTileSpriteSheet1 =
        new Sprite(gameRenderer, "./assets/water_tile_2_sheet.png", 10, 3);

    seaTileSpriteSheet =
        new Sprite(gameRenderer, "./assets/water_tile_1_sheet.png", 10, 3);
  } catch (const std::runtime_error &ex) {
    throw;
  }
  // END: Asset loading

  
  // BEGIN: Constant setup and state init
  std::pair<float, float> cameraPosition = std::make_pair(0, 0);

  SDL_FRect playerPositioningRect = {.x = centerCamera(cameraPosition, std::make_pair(screenWidth, screenHeight), std::make_pair(playerSpriteN->getFrameWidth(), playerSpriteN->getFrameHeight())).first,
                                     .y = centerCamera(cameraPosition, std::make_pair(screenWidth, screenHeight), std::make_pair(playerSpriteN->getFrameWidth(), playerSpriteN->getFrameHeight())).second,
                                     .w = playerSpriteN->getFrameWidth(),
                                     .h = playerSpriteN->getFrameHeight()};
  SpriteState spriteState = {.direction = North};

  // END: Constant setup and state init

  /* Game loop */
  while (true) {
    std::cout << cameraPosition.first << " " << cameraPosition.second << std::endl;
    std::cout << isoMapSector->pointIntersects(cameraPosition)
              << std::endl
              << std::endl;
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

    /* Lay tiles with SpriteSheet */
    SDL_FRect tilePositionRect = {
        .x = 0,
        .y = centerCamera(cameraPosition, std::make_pair(screenWidth, screenHeight), std::make_pair(seaTileSpriteSheet->getFrameWidth(), seaTileSpriteSheet->getFrameHeight())).second,
        .w = seaTileSpriteSheet->getFrameWidth(),
        .h = seaTileSpriteSheet->getFrameHeight()};

    // seaTileSpriteSheet->renderTick(&tilePositionRect);
    int visible_tiles_x = screenWidth / seaTileSpriteSheet->getFrameWidth();
    int visible_tiles_y =
        (screenHeight / (seaTileSpriteSheet->getFrameHeight() / 2));
    for (int y = 0; y < visible_tiles_y; ++y) {
      for (int x = 0; x < visible_tiles_x; ++x) {
        if (y % 2 == 0) {
          tilePositionRect.x =
              centerCamera(cameraPosition, std::make_pair(screenWidth, screenHeight), std::make_pair(seaTileSpriteSheet->getFrameWidth(), seaTileSpriteSheet->getFrameHeight())).first + (x * seaTileSpriteSheet->getFrameWidth());
        } else {
          // Every other row has a negative offset of half the tile width.
          tilePositionRect.x =
              centerCamera(cameraPosition, std::make_pair(screenWidth, screenHeight), std::make_pair(seaTileSpriteSheet->getFrameWidth(), seaTileSpriteSheet->getFrameHeight())).first + (x * seaTileSpriteSheet->getFrameWidth()) + (seaTileSpriteSheet->getFrameWidth() / 2);
        }

        seaTileSpriteSheet->renderTick(&tilePositionRect);
      }
      tilePositionRect.y -= (seaTileSpriteSheet->getFrameHeight() / 2);
    }

    /* Render player sprite with SpriteSheet */
    Sprite *playerSprite = playerSpriteSelector->selectSprite(spriteState);
    if (playerSprite != NULL) {
      playerSprite->renderTick(&playerPositioningRect);
    }

    SDL_RenderPresent(gameRenderer);
    SDL_Delay(10);
  }

  return 0;
}