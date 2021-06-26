#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>

using namespace std;

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

SDL_Texture *loadGameTextureAsset(std::string path, SDL_Renderer *renderer) {
  SDL_Surface *imageAsset = IMG_Load(path.c_str());
  if (imageAsset == NULL) {
    throw std::runtime_error("unable to load image");
  }

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

  SDL_Texture *playerSpriteSheetTexture = NULL;
  SDL_Texture *isometricBackgroundTexture = NULL;
  try {
    playerSpriteSheetTexture = loadGameTextureAsset(
        "./assets/isometric_box_sprite_sheet.png", gameRenderer);
    isometricBackgroundTexture =
        loadGameTextureAsset("./assets/iso_metric_grid.png", gameRenderer);
  } catch (const std::runtime_error &ex) {
    throw;
  }

  SDL_FRect playerPositioningRect = {
      .x = 0.0, .y = 0.0, .w = 198.0, .h = 132.0};
  SDL_Rect playerSpriteSheetClippingRect = {.x = 0, .y = 0, .w = 200, .h = 132};

  KEY_STATE keyState = {
      .up = false, .down = false, .left = false, .right = false};
  while (true) {
    SDL_Event event;

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

    if (keyState.left) {
      playerPositioningRect.x += calculateHorizontalVectorComponent(-velocity);
      playerPositioningRect.y += calculateVerticalVectorComponent(-velocity);
      playerSpriteSheetClippingRect.x = 600;
      playerSpriteSheetClippingRect.y = 0;
    } else if (keyState.right) {
      playerPositioningRect.x += calculateHorizontalVectorComponent(velocity);
      playerPositioningRect.y += calculateVerticalVectorComponent(velocity);
      playerSpriteSheetClippingRect.x = 200;
      playerSpriteSheetClippingRect.y = 0;
    } else if (keyState.up) {
      playerPositioningRect.x += calculateHorizontalVectorComponent(velocity);
      playerPositioningRect.y += calculateVerticalVectorComponent(-velocity);
      playerSpriteSheetClippingRect.x = 0;
      playerSpriteSheetClippingRect.y = 0;
    } else if (keyState.down) {
      playerPositioningRect.x += calculateHorizontalVectorComponent(-velocity);
      playerPositioningRect.y += calculateVerticalVectorComponent(velocity);
      playerSpriteSheetClippingRect.x = 400;
      playerSpriteSheetClippingRect.y = 0;
    }

    SDL_RenderClear(gameRenderer);
    SDL_RenderCopyF(gameRenderer, isometricBackgroundTexture, NULL, NULL);
    SDL_RenderCopyF(gameRenderer, playerSpriteSheetTexture,
                    &playerSpriteSheetClippingRect, &playerPositioningRect);
    SDL_RenderPresent(gameRenderer);
  }

  return 0;
}