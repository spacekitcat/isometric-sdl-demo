#include <SDL.h>
#include <SDL_keyboard.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iomanip>
#include <math.h>
#include <random>
#include <sstream>

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

bool isNorthWestPressed(const Uint8 *state) {
  return (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) &&
         (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]);
}

bool isNorthEastPressed(const Uint8 *state) {
  return (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) &&
         (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]);
}

bool isSouthWestPressed(const Uint8 *state) {
  return (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) &&
         (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]);
}

bool isSouthEastPressed(const Uint8 *state) {
  return (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) &&
         (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]);
}

bool isNorthPressed(const Uint8 *state) {
  return state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W];
}

bool isSouthPressed(const Uint8 *state) {
  return state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S];
}

bool isEastPressed(const Uint8 *state) {
  return state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D];
}

bool isWestPressed(const Uint8 *state) {
  return state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A];
}

SpriteStateDirectionEnum getInputDirection(const Uint8 *state) {
  if (isNorthWestPressed(state)) {
    return NorthWest;
  } else if (isNorthEastPressed(state)) {
    return NorthEast;
  } else if (isSouthWestPressed(state)) {
    return SouthWest;
  } else if (isSouthEastPressed(state)) {
    return SouthEast;
  } else if (isSouthPressed(state)) {
    return South;
  } else if (isNorthPressed(state)) {
    return North;
  } else if (isEastPressed(state)) {
    return East;
  } else if (isWestPressed(state)) {
    return West;
  } else {
    return Idle;
  }
}

bool noKeysPressed(const Uint8 *state) {
  return !(isNorthWestPressed(state) || isNorthEastPressed(state) ||
           isSouthWestPressed(state) || isSouthEastPressed(state) ||
           isNorthPressed(state) || isSouthPressed(state) ||
           isEastPressed(state) || isWestPressed(state));
}

int main() {
  auto map = new int[255][255];

  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(1, 3);
  for (int i = 0; i < 255; ++i) {
    for (int j = 0; j < 255; ++j) {
      map[i][j] = uniform_dist(e1);
    }
  }

  const int screenWidth = 800;
  const int screenHeight = 600;

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

  if (Mix_PlayChannel(-1, sample, 0) == -1) {
    printf("Mix_PlayMusic: %s\n", Mix_GetError());
    // well, there's no music, but most games don't break without music...
  }
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

    seaTileSpriteSheet =
        new Sprite(gameRenderer, "./assets/water_tile_1_sheet.png", 10, 3);
  } catch (const std::runtime_error &ex) {
    throw;
  }
  // END: Asset loading

  // BEGIN: Constant setup and state init
  SDL_FRect playerPositioningRect = {
      .x = (screenWidth / 2) - (seaTileSpriteSheet->getFrameWidth()),
      .y = (screenHeight / 2) - (seaTileSpriteSheet->getFrameHeight()),
      .w = playerSpriteN->getFrameWidth(),
      .h = playerSpriteN->getFrameHeight()};

  SpriteState spriteState = {.direction = North};

  float cam_x = 0.0;
  float cam_y = 0.0;
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

    /* Read and process input control keys */

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (!noKeysPressed(keyState)) {
      spriteState.direction = getInputDirection(keyState);

      switch (spriteState.direction) {
      case NorthWest:
        cam_x -= calculateHorizontalVectorComponent(-1);
        cam_y -= calculateVerticalVectorComponent(-1);
        break;
      case NorthEast:
        cam_x -= calculateHorizontalVectorComponent(1);
        cam_y -= calculateVerticalVectorComponent(-1);
        break;
      case SouthEast:
        cam_x -= calculateHorizontalVectorComponent(1);
        cam_y -= calculateVerticalVectorComponent(1);
        break;
      case SouthWest:
        cam_x -= calculateHorizontalVectorComponent(-1);
        cam_y -= calculateVerticalVectorComponent(1);
        break;
      case South:
        cam_y -= 1;
        break;
      case North:
        cam_y -= -1;
        break;
      case East:
        cam_x -= 1;
        break;
      case West:
        cam_x -= -1;
        break;
      }
    }

    SDL_RenderClear(gameRenderer);

    /* Lay tiles with SpriteSheet */
    SDL_FRect tilePositionRect = {.x = 0.0,
                                  .y = cam_y -
                                       seaTileSpriteSheet->getFrameHeight(),
                                  .w = seaTileSpriteSheet->getFrameWidth(),
                                  .h = seaTileSpriteSheet->getFrameHeight()};

    int visible_tiles_x = screenWidth / seaTileSpriteSheet->getFrameWidth();
    int visible_tiles_y =
        (screenHeight / (seaTileSpriteSheet->getFrameHeight() / 2)) * 2;
    for (int i = 0; i < visible_tiles_y; ++i) {
      if (i % 2 == 0) {
        tilePositionRect.x = cam_x;
      } else {
        // Every other row has a negative offset of half the tile width.
        tilePositionRect.x = cam_x - (seaTileSpriteSheet->getFrameWidth() / 2);
      }
      tilePositionRect.y += seaTileSpriteSheet->getFrameHeight() / 2;
      seaTileSpriteSheet->renderTick(&tilePositionRect);

      for (int j = 0; j < visible_tiles_x; ++j) {
        tilePositionRect.x += seaTileSpriteSheet->getFrameWidth();

        seaTileSpriteSheet->renderTick(&tilePositionRect);
      }
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