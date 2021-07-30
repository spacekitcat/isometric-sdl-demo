#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <chrono>
#include <random>
#include "spritesheets/spritesheet.hpp"
#include <SDL_keyboard.h>

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

#define PI 3.14159265

struct KEY_STATE {
  bool up;
  bool down;
  bool right;
  bool left;
};

float calculateHorizontalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * cos(26.6 * PI / 180.0);
}

float calculateVerticalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * sin(26.6 * PI / 180.0);
}

SDL_Surface *loadGameImageAsset(std::string path) {
  SDL_Surface *imageAsset = IMG_Load(path.c_str());
  if (imageAsset == NULL) {
    throw std::runtime_error("unable to load image");
  }

  return imageAsset;
}

SDL_Texture *loadGameTextureAsset(SDL_Surface *imageAsset, SDL_Renderer *renderer) {
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, imageAsset);
  SDL_SetColorKey(imageAsset, SDL_TRUE,
                  SDL_MapRGB(imageAsset->format, 255, 255, 255));

  return texture;
}

int main() {
  auto map = new int [255][255];

  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(0, 1);
  for (int i=0; i<255; ++i) {
    for (int j=0; j<255; ++j) {
      map[i][j] = uniform_dist(e1);
    }
  }

  const int screenWidth = 800;
  const int screenHeight = 600;
  const float velocity = 1;


  // BEGIN: SDL Setup area
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *screen = SDL_CreateWindow(
      "SDL2Application4 (isometric demo)", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  SDL_Renderer *gameRenderer =
      SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

  // END: SDL Setup area

  // BEGIN: Asset loading
  SDL_Surface *playerSpriteSheetSurface = NULL;
  SDL_Surface *isometricBackgroundSurface = NULL;
  SDL_Surface *isometricBackgroundSurface2 = NULL;

  try {
    playerSpriteSheetSurface = loadGameImageAsset("./assets/Rendered spritesheets/boat_iso.png");
    isometricBackgroundSurface = loadGameImageAsset("./assets/Rendered\ spritesheets/water_tile_0_sheet.png");
    isometricBackgroundSurface2 = loadGameImageAsset("./assets/Rendered\ spritesheets/water_tile_1_sheet.png");
  } catch (const std::runtime_error &ex) {
    throw;
  }

  SpriteSheet *boatSpriteSheet = new SpriteSheet(gameRenderer, playerSpriteSheetSurface, 4, 2);
  SpriteSheet *seaTileSpriteSheet = new SpriteSheet(gameRenderer, isometricBackgroundSurface, 10, 10);
  SpriteSheet *seaTileSpriteSheet2 = new SpriteSheet(gameRenderer, isometricBackgroundSurface2, 10, 10);

  // END: Asset loading

  // BEGIN: Constant setup and state init
  // TODO: This needs a better abstraction.
  float tileXOffsetConstant = (isometricBackgroundSurface->w / 10) - 2;
  float tileYOffsetConstant = (isometricBackgroundSurface->h / 10) / 2 - 2;

  int visible_tiles_x = screenWidth / tileXOffsetConstant;
  int visible_tiles_y = (screenHeight / tileYOffsetConstant) + 2;

  SDL_FRect playerPositioningRect = {
      .x = screenWidth/2 - 64, .y = screenHeight/2 - 64, .w = playerSpriteSheetSurface->w / 4, .h = playerSpriteSheetSurface->h / 2};

  KEY_STATE keyState = {
      .up = false, .down = false, .left = false, .right = false};

  SDL_FRect tilePositionRect = {.x = 0.0, .y = 0.0, .w = isometricBackgroundSurface->w / 10 , .h = isometricBackgroundSurface->h / 10 };

  float cam_x = 0.0;
  float cam_y = 0.0;
  int backgroundTileAnimationFrame = 0;
  int playerSpriteFrame = 0;
  // END: Constant setup and state init

  Uint32 rotLoop = 0;
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

    // TODO: Give sprite sheet 8 directions and add 4 new listeners for NW, NE, SE and SW (to fix dodgey velocity component code on multiple key presses)
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if ((state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) && (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A])) {
      cam_x -= calculateHorizontalVectorComponent(-1);
      cam_y -= calculateVerticalVectorComponent(-1);
      
      playerSpriteFrame = 6;
    } else if ((state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) && (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])) {
      cam_x -= calculateHorizontalVectorComponent(1);
      cam_y -= calculateVerticalVectorComponent(-1);

      playerSpriteFrame = 4;
    } else if ((state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) && (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_A])) {
      cam_x -= calculateHorizontalVectorComponent(-1);
      cam_y -= calculateVerticalVectorComponent(1);

      playerSpriteFrame = 0;
    } else if ((state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) && (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])) {
      cam_x -= calculateHorizontalVectorComponent(1);
      cam_y -= calculateVerticalVectorComponent(1);

      playerSpriteFrame = 2;
    } else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
      cam_y -= 1;
      playerSpriteFrame = 1;
    } else if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
      cam_y -= -1;
      playerSpriteFrame = 5;
    } else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_D]) {
      cam_x -= 1;
      playerSpriteFrame = 3;
    } else if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_A]) {
      cam_x -= -1;
      playerSpriteFrame = 7;
    } else {
      if (SDL_GetTicks() > rotLoop + 50) {
        ++playerSpriteFrame;
        if (playerSpriteFrame > 7) {
          playerSpriteFrame = 0;
        }
        rotLoop = SDL_GetTicks();
      }
  }

    SDL_RenderClear(gameRenderer);

    /* Lay tiles with SpriteSheet */
    tilePositionRect.y = cam_y - (tileYOffsetConstant * 2) - 300;
    backgroundTileAnimationFrame = (SDL_GetTicks() / 128) % 39;
    for (int i=0; i<visible_tiles_y * 2; ++i) {
      if (i%2 == 0) {
        tilePositionRect.x = cam_x - 100;
      } else {
        tilePositionRect.x = cam_x - (tileXOffsetConstant / 2) - 100;
      }
      tilePositionRect.y += tileYOffsetConstant - 1;
      seaTileSpriteSheet->render(&tilePositionRect, backgroundTileAnimationFrame);

      for (int j=0; j<visible_tiles_x * 2; ++j) {
        tilePositionRect.x += tileXOffsetConstant;
        
        if (map[i][j] == 1) {
          seaTileSpriteSheet2->render(&tilePositionRect, backgroundTileAnimationFrame);
        } else {
          seaTileSpriteSheet->render(&tilePositionRect, backgroundTileAnimationFrame);
        }
      }
    }

    /* Render player sprite with SpriteSheet */
    boatSpriteSheet->render(&playerPositioningRect, playerSpriteFrame);
    SDL_RenderPresent(gameRenderer);

    SDL_Delay(10);

  }

  return 0;
}