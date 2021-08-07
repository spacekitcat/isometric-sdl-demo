#include "sprite.hpp"

Sprite::Sprite() {
    
}

Sprite::Sprite(SDL_Renderer *renderer, SDL_Surface *spriteSheetSurface, int columns, int rows) {
    this->renderer = renderer;
    this->spriteSheetSurface = spriteSheetSurface;
    this->spriteSheetTexture = SDL_CreateTextureFromSurface(this->renderer, this->spriteSheetSurface);
    this->_columns = columns;
    this->_rows = rows;
    SDL_SetColorKey(this->spriteSheetSurface, SDL_TRUE, SDL_MapRGB(this->spriteSheetSurface->format, 255, 255, 255));
    this->_animationInterval = 200;
    this->_currentFrame = 0;
}

Sprite::~Sprite() {

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

    SDL_RenderCopyF(this->renderer, this->spriteSheetTexture, &clippingRect, position);
}

void Sprite::renderTick(SDL_FRect *position) {
    this->_currentFrame = (SDL_GetTicks() / this->_animationInterval) % this->getFrameCount();
    this->render(position, this->_currentFrame);
}

int Sprite::getFrameCount() {
    return this->_rows * this->_columns;
}

int Sprite::getColumnCount() {
    return this->_columns;
}

int Sprite::getRowCount() {
    return this->_rows;
}

float Sprite::getFrameWidth() {
    return this->spriteSheetSurface->w / this->_columns;
}

float Sprite::getFrameHeight() {
    return this->spriteSheetSurface->h / this->_rows;
}