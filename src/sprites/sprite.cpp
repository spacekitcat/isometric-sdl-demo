#include "sprite.hpp"
#include <SDL.h>
#include <SDL_Image.h>

Sprite::Sprite() {}

Sprite::Sprite(SDL_Renderer *renderer, std::string spriteSheetPath, int columns,
               int rows) {
  this->spriteSheetSurface = NULL;
  this->spriteSheetTexture = NULL;

  try {
    this->spriteSheetSurface = loadGameImageAsset(spriteSheetPath);
  } catch (const std::runtime_error &ex) {
    throw;
  }

  this->renderer = renderer;
  this->spriteSheetSurface = spriteSheetSurface;
  this->spriteSheetTexture =
      SDL_CreateTextureFromSurface(this->renderer, this->spriteSheetSurface);
  this->_columns = columns;
  this->_rows = rows;
  SDL_SetColorKey(this->spriteSheetSurface, SDL_TRUE,
                  SDL_MapRGB(this->spriteSheetSurface->format, 255, 255, 255));
  this->_animationInterval = 200;
  this->_currentFrame = 0;
}

Sprite::~Sprite() {
    free(this->spriteSheetSurface);
    this->spriteSheetSurface = NULL;

    free(this->spriteSheetTexture);
    this->spriteSheetTexture = NULL;

}

SDL_Surface *Sprite::loadGameImageAsset(std::string path) {
  SDL_Surface *imageAsset = IMG_Load(path.c_str());
  if (imageAsset == NULL) {
    throw std::runtime_error("unable to load image");
  }

  return imageAsset;
}

void Sprite::_updateSpriteFrame(int index, SDL_Rect *clippingFrame) {
  int row = round(index / this->_columns);
  int column = round(index % this->_columns);

  float frameWidth = this->spriteSheetSurface->w / this->_columns;
  float frameHeight = this->spriteSheetSurface->h / this->_rows;

  clippingFrame->x = column * frameWidth;
  clippingFrame->y = row * frameHeight;
  clippingFrame->w = frameWidth;
  clippingFrame->h = frameHeight;
}

void Sprite::render(SDL_FRect *position, int frame) {
  SDL_Rect clippingRect;

  this->_updateSpriteFrame(frame, &clippingRect);

  SDL_RenderCopyF(this->renderer, this->spriteSheetTexture, &clippingRect,
                  position);
}

void Sprite::renderTick(SDL_FRect *position) {
  this->_currentFrame =
      (SDL_GetTicks() / this->_animationInterval) % this->getFrameCount();
  this->render(position, this->_currentFrame);
}

int Sprite::getFrameCount() { return this->_rows * this->_columns; }

int Sprite::getColumnCount() { return this->_columns; }

int Sprite::getRowCount() { return this->_rows; }

float Sprite::getFrameWidth() {
  return this->spriteSheetSurface->w / this->_columns;
}

float Sprite::getFrameHeight() {
  return this->spriteSheetSurface->h / this->_rows;
}