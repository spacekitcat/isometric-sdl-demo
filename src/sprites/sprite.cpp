#include "sprite.hpp"
#include <SDL.h>
#include <SDL_image.h>

Sprite::Sprite(SDLManager *sdlManager, std::string spriteSheetPath, int columns,
               int rows) {
  this->spriteSheetSurface = nullptr;
  this->spriteSheetTexture = nullptr;

  try {
    this->spriteSheetSurface = loadGameImageAsset(spriteSheetPath);
  } catch (const std::runtime_error &ex) {
    throw;
  }

  _sdlManager = sdlManager;
  this->spriteSheetTexture =
      SDL_CreateTextureFromSurface(_sdlManager->getRenderer(), this->spriteSheetSurface);
  this->_columns = columns;
  this->_rows = rows;
  SDL_SetColorKey(this->spriteSheetSurface, SDL_TRUE,
                  SDL_MapRGB(this->spriteSheetSurface->format, 255, 255, 255));
  this->_animationInterval = 200;
  this->_currentFrame = 0;
}

Sprite::~Sprite() {
    free(this->spriteSheetSurface);
    this->spriteSheetSurface = nullptr;

    free(this->spriteSheetTexture);
    this->spriteSheetTexture = nullptr;

}

SDL_Surface *Sprite::loadGameImageAsset(std::string path) {
  SDL_Surface *imageAsset = IMG_Load(path.c_str());
  if (imageAsset == nullptr) {
    throw std::runtime_error("unable to load image");
  }

  return imageAsset;
}

void Sprite::_updateSpriteFrame(int index, SDL_Rect *clippingFrame) {
  int row = round(index / this->_columns);
  int column = round(index % this->_columns);

  int frameWidth = this->spriteSheetSurface->w / this->_columns;
  int frameHeight = this->spriteSheetSurface->h / this->_rows;

  clippingFrame->x = column * frameWidth;
  clippingFrame->y = row * frameHeight;
  clippingFrame->w = frameWidth;
  clippingFrame->h = frameHeight;
}

void Sprite::render(float xPosition, float yPosition, int frame) {
  SDL_Rect clippingRect;
  SDL_FRect positionRect = { .w=this->getFrameWidth(), .h=this->getFrameHeight() };
  positionRect.x = xPosition; // + (this->getFrameWidth() / 2);
  positionRect.y = yPosition - this->getFrameHeight();
  this->_updateSpriteFrame(frame, &clippingRect);

  SDL_RenderCopyF(_sdlManager->getRenderer(), this->spriteSheetTexture, &clippingRect,
                  &positionRect);
}

void Sprite::renderTick(SDL_FRect *position) {
  this->_currentFrame =
      (SDL_GetTicks() / this->_animationInterval) % this->getFrameCount();
    this->render(position->x, position->y, this->_currentFrame);
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