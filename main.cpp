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

void updateSpriteSheetFrame(int index, SDL_Surface *spriteSheet, SDL_Rect *clippingFrame) {
  const int framesPerSpriteSheet = 4;
  const int spritesPerAxis = framesPerSpriteSheet / 2;

  float frameWidth = spriteSheet->w / spritesPerAxis;
  float frameHeight = spriteSheet->h / spritesPerAxis;

  clippingFrame->w = frameWidth;
  clippingFrame->h = frameHeight;
  if (index == 0) {
    clippingFrame->x = 0;
    clippingFrame->y = 0;
  } else if (index == 1) {
    clippingFrame->x = frameWidth;
    clippingFrame->y = 0;
  } else if (index == 2) {
    clippingFrame->x = 0;
    clippingFrame->y = frameHeight;
  } else if (index == 3) {
    clippingFrame->x = frameWidth;
    clippingFrame->y = frameHeight;
  }
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;
  const float velocity = 1;

  float tileXOffsetConstant = 125.0;
  float tileYOffsetConstant = 62.0;

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
  SDL_Texture *playerSpriteSheetTexture = NULL;
  SDL_Surface *isometricBackgroundSurface = NULL;
  SDL_Texture *isometricBackgroundTexture = NULL;
  try {
    playerSpriteSheetSurface = loadGameImageAsset("./assets/Rendered\ spritesheets/boat_iso.png");
    playerSpriteSheetTexture = loadGameTextureAsset(playerSpriteSheetSurface, gameRenderer);
    isometricBackgroundSurface = loadGameImageAsset("./assets/tile0.png");
    isometricBackgroundTexture = loadGameTextureAsset(isometricBackgroundSurface, gameRenderer);
  } catch (const std::runtime_error &ex) {
    throw;
  }


  SDL_FRect playerPositioningRect = {
      .x = 0.0, .y = 0.0, .w = playerSpriteSheetSurface->w / 2, .h = playerSpriteSheetSurface->h / 2};
  SDL_Rect playerSpriteSheetClippingRect;
  updateSpriteSheetFrame(1, playerSpriteSheetSurface, &playerSpriteSheetClippingRect);

  KEY_STATE keyState = {
      .up = false, .down = false, .left = false, .right = false};

  SDL_FRect tilePositionRect = {.x = 0.0, .y = 0.0, .w = isometricBackgroundSurface->w, .h = isometricBackgroundSurface->h };

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

      updateSpriteSheetFrame(3, playerSpriteSheetSurface, &playerSpriteSheetClippingRect);
    } else if (keyState.right) {
      playerPositioningRect.x += calculateHorizontalVectorComponent(velocity);
      playerPositioningRect.y += calculateVerticalVectorComponent(velocity);
      
      updateSpriteSheetFrame(1, playerSpriteSheetSurface, &playerSpriteSheetClippingRect);
    } else if (keyState.up) {
                  playerPositioningRect.x += calculateHorizontalVectorComponent(velocity);
      playerPositioningRect.y += calculateVerticalVectorComponent(-velocity);
     
      updateSpriteSheetFrame(2, playerSpriteSheetSurface, &playerSpriteSheetClippingRect);

    } else if (keyState.down) {
      playerPositioningRect.x += calculateHorizontalVectorComponent(-velocity);
      playerPositioningRect.y += calculateVerticalVectorComponent(velocity);

      updateSpriteSheetFrame(0, playerSpriteSheetSurface, &playerSpriteSheetClippingRect);
    }

    SDL_RenderClear(gameRenderer);

    tilePositionRect.y = -tileYOffsetConstant;
    for (int i=0; i<11; ++i) {
      tilePositionRect.x = -tileXOffsetConstant;
      SDL_RenderCopyF(gameRenderer, isometricBackgroundTexture, NULL, &tilePositionRect);
      for (int j=0; j<6; ++j) {
        tilePositionRect.x += tileXOffsetConstant;
        SDL_RenderCopyF(gameRenderer, isometricBackgroundTexture, NULL, &tilePositionRect);
      }
      tilePositionRect.y += tileYOffsetConstant;
    }

    SDL_RenderCopyF(gameRenderer, playerSpriteSheetTexture,
                    &playerSpriteSheetClippingRect, &playerPositioningRect);
    SDL_RenderCopyF(gameRenderer, playerSpriteSheetTexture,
                    &playerSpriteSheetClippingRect, &playerPositioningRect);
    SDL_RenderPresent(gameRenderer);

    SDL_Delay(1);
  }

  return 0;
}