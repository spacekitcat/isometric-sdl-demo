#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <chrono>
#include "spritesheets/spritesheet.hpp"

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
  return vectorMagnitude * cos(26.6 * PI / 180.0) * 2;
}

float calculateVerticalVectorComponent(float vectorMagnitude) {
  return vectorMagnitude * sin(26.6 * PI / 180.0) * 2;
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
  const int screenWidth = 800;
  const int screenHeight = 600;
  const float velocity = 1;

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

  SDL_Surface *playerSpriteSheetSurface = NULL;
  SDL_Surface *isometricBackgroundSurface = NULL;

  try {
    playerSpriteSheetSurface = loadGameImageAsset("./assets/Rendered spritesheets/boat_iso.png");
    isometricBackgroundSurface = loadGameImageAsset("./assets/Rendered spritesheets/water_tile_0_sheet.png");
  } catch (const std::runtime_error &ex) {
    throw;
  }

  float tileXOffsetConstant = (isometricBackgroundSurface->w / 10) - 2;
  float tileYOffsetConstant = (isometricBackgroundSurface->h / 10) / 2 - 2;

  int visible_tiles_x = screenWidth / tileXOffsetConstant;
  int visible_tiles_y = (screenHeight / tileYOffsetConstant) + 2;

  SDL_FRect playerPositioningRect = {
      .x = screenWidth/2 - 64, .y = screenHeight/2 - 64, .w = playerSpriteSheetSurface->w / 2, .h = playerSpriteSheetSurface->h / 2};

  KEY_STATE keyState = {
      .up = false, .down = false, .left = false, .right = false};

  SDL_FRect tilePositionRect = {.x = 0.0, .y = 0.0, .w = isometricBackgroundSurface->w / 10 , .h = isometricBackgroundSurface->h / 10 };

  float cam_x = 0.0;
  float cam_y = 0.0;
  SpriteSheet *boatSpriteSheet = new SpriteSheet(gameRenderer, playerSpriteSheetSurface, 2, 2);
  SpriteSheet *seaTileSpriteSheet = new SpriteSheet(gameRenderer, isometricBackgroundSurface, 10, 10);
  int backgroundTileAnimationFrame = 0;
  int playerSpriteFrame = 0;
  while (true) {
    SDL_Event event;

    /* Process events and key states */
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        return 0;
        break;

      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
          break;
        case SDLK_UP:
        case SDLK_w:
          keyState.up = true;
          break;
        case SDLK_DOWN:
        case SDLK_s:
          keyState.down = true;
          break;
        case SDLK_LEFT:
        case SDLK_a:
          keyState.left = true;
          break;
        case SDLK_RIGHT:
        case SDLK_d:
          keyState.right = true;
          break;
        }
        break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
          return 0;
          break;
        case SDLK_UP:
        case SDLK_w:
          keyState.up = false;
          break;
        case SDLK_DOWN:
        case SDLK_s:
          keyState.down = false;
          break;
        case SDLK_LEFT:
        case SDLK_a:
          keyState.left = false;
          break;
        case SDLK_RIGHT:
        case SDLK_d:
          keyState.right = false;
          break;
        }
        break;
      }
    }

    /* Apply velcity components and select sprite from key state */
    if (keyState.left) {
      cam_x -= calculateHorizontalVectorComponent(-1);
      cam_y -= calculateVerticalVectorComponent(-1);
      playerSpriteFrame = 3;

    } else if (keyState.right) {
      cam_x -= calculateHorizontalVectorComponent(1);
      cam_y -= calculateVerticalVectorComponent(1);
      playerSpriteFrame = 1;

    } else if (keyState.up) {
      cam_x -= calculateHorizontalVectorComponent(1);
      cam_y -= calculateVerticalVectorComponent(-1);
      playerSpriteFrame = 2;

    } else if (keyState.down) {
      cam_x += calculateHorizontalVectorComponent(1);
      cam_y += calculateVerticalVectorComponent(-1);
      playerSpriteFrame = 0;

    }

    SDL_RenderClear(gameRenderer);

    /* Lay tiles with SpriteSheet */
    tilePositionRect.y = cam_y - (tileYOffsetConstant * 2) - 300;
    backgroundTileAnimationFrame = (SDL_GetTicks() / 128) % 100;
    for (int i=0; i<visible_tiles_y * 2; ++i) {
      if (i%2 == 0) {
        tilePositionRect.x = cam_x - 100;
      } else {
        tilePositionRect.x = cam_x - (tileXOffsetConstant / 2) - 100;
      }
      tilePositionRect.y += tileYOffsetConstant;
      seaTileSpriteSheet->render(&tilePositionRect, backgroundTileAnimationFrame);

      for (int j=0; j<visible_tiles_x * 2; ++j) {
        tilePositionRect.x += tileXOffsetConstant;
        
        seaTileSpriteSheet->render(&tilePositionRect, backgroundTileAnimationFrame);
      }
    }

    /* Render player sprite with SpriteSheet */
    boatSpriteSheet->render(&playerPositioningRect, playerSpriteFrame);
    SDL_RenderPresent(gameRenderer);

    SDL_Delay(5);
  }

  return 0;
}