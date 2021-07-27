#include "spritesheet.hpp"

SpriteSheet::SpriteSheet(SDL_Renderer *renderer, SDL_Surface *spriteSheetSurface, int columns, int rows) {
    this->renderer = renderer;
    this->spriteSheetSurface = spriteSheetSurface;
    this->spriteSheetTexture = SDL_CreateTextureFromSurface(this->renderer, this->spriteSheetSurface);
    SDL_SetColorKey(this->spriteSheetSurface, SDL_TRUE, SDL_MapRGB(this->spriteSheetSurface->format, 255, 255, 255));
}

SpriteSheet::~SpriteSheet() {

}

void SpriteSheet::_updateSpriteSheetFrame(int index, SDL_Surface *spriteSheet, SDL_Rect *clippingFrame) {  
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

void SpriteSheet::render(SDL_FRect *position, int frame) {
    SDL_Rect clippingRect;
    this->_updateSpriteSheetFrame(frame, this->spriteSheetSurface, &clippingRect);

    SDL_RenderCopyF(this->renderer, this->spriteSheetTexture, &clippingRect, position);
}