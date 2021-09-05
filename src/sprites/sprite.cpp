#include "sprite.hpp"

Sprite::Sprite(std::shared_ptr<SDLManager> sdlManager) {
  _drawBoundingBox = false;
  _spritesheetSurface = nullptr;
  _spritesheetTexture = nullptr;
  _sdlManager = sdlManager;

  assert(_sdlManager != nullptr);

  this->_animationInterval = 200;
  this->_currentFrame = 0;
}

Sprite::~Sprite() {
  free(_spritesheetSurface);
  _spritesheetSurface = nullptr;

  free(_spritesheetTexture);
  _spritesheetTexture = nullptr;
}

void Sprite::setSpritesheet(std::string spritesheetPath,
                            struct SpriteMetadata *metadata) {
  _spritesheetSurface = nullptr;
  _spritesheetTexture = nullptr;

  try {
    _spritesheetSurface = loadGameImageAsset(spritesheetPath);
  } catch (const std::runtime_error &ex) {
    throw;
  }

  _spritesheetTexture = SDL_CreateTextureFromSurface(_sdlManager->getRenderer(),
                                                     _spritesheetSurface);
  this->_columns = metadata->columns;
  this->_rows = metadata->rows;
  SDL_SetColorKey(_spritesheetSurface, SDL_TRUE,
                  SDL_MapRGB(_spritesheetSurface->format, 255, 255, 255));
}

SDL_Surface *Sprite::loadGameImageAsset(std::string path) {
  SDL_Surface *imageAsset = IMG_Load(path.c_str());
  if (imageAsset == nullptr) {
    throw std::runtime_error("unable to load image");
  }

  return imageAsset;
}

void Sprite::updateSpriteFrame(int index, SDL_Rect *clippingFrame) {
  int row = round(index / _columns);
  int column = round(index % _columns);

  int frameWidth = this->getFrameWidth();
  int frameHeight = this->getFrameHeight();

  clippingFrame->x = column * frameWidth;
  clippingFrame->y = row * frameHeight;
  clippingFrame->w = frameWidth;
  clippingFrame->h = frameHeight;
}

void Sprite::render(float xPosition, float yPosition, int frame) {
  SDL_Rect clippingRect;
  SDL_FRect positionRect = {.w = this->getFrameWidth(),
                            .h = this->getFrameHeight()};
  positionRect.x = xPosition; // + (this->getFrameWidth() / 2);
  positionRect.y = yPosition - this->getFrameHeight();
  this->updateSpriteFrame(frame, &clippingRect);

  SDL_RenderCopyF(_sdlManager->getRenderer(), _spritesheetTexture,
                  &clippingRect, &positionRect);

  if (_drawBoundingBox) {
    SDL_Rect playerRect = {
        .x = xPosition,
        .y = yPosition,
        .w = this->getFrameWidth(),
        .h = -this->getFrameHeight(),
    };

    SDL_SetRenderDrawColor(_sdlManager->getRenderer(), 255, 255, 255, 255);
    SDL_RenderDrawRect(_sdlManager->getRenderer(), &playerRect);
  }
}

void Sprite::renderTick(SDL_FRect *position) {
  this->_currentFrame =
      (SDL_GetTicks() / this->_animationInterval) % this->getFrameCount();
  this->render(position->x, position->y, this->_currentFrame);
}

int Sprite::getFrameCount() { return _rows * _columns; }

int Sprite::getColumnCount() { return _columns; }

int Sprite::getRowCount() { return _rows; }

float Sprite::getFrameWidth() { return _spritesheetSurface->w / _columns; }

float Sprite::getFrameHeight() { return _spritesheetSurface->h / _rows; }

void Sprite::setRenderBoundingBox(bool render) { _drawBoundingBox = render; }

std::pair<float, float> Sprite::getDimensions() {
  return std::make_pair(this->getFrameWidth(), this->getFrameHeight());
}