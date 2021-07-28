#include "spritesheet.hpp"

SpriteSheet::SpriteSheet(SDL_Renderer *renderer, SDL_Surface *spriteSheetSurface, int columns, int rows) {
    this->renderer = renderer;
    this->spriteSheetSurface = spriteSheetSurface;
    this->spriteSheetTexture = SDL_CreateTextureFromSurface(this->renderer, this->spriteSheetSurface);
    this->_columns = columns;
    this->_rows = rows;
    SDL_SetColorKey(this->spriteSheetSurface, SDL_TRUE, SDL_MapRGB(this->spriteSheetSurface->format, 255, 255, 255));
}

SpriteSheet::~SpriteSheet() {


}

void SpriteSheet::_updateSpriteSheetFrame(int index, SDL_Rect *clippingFrame) {  
    int row = round(index / this->_rows);
    int column = round(index % this->_columns);
    float frameWidth = this->spriteSheetSurface->w / this->_columns;
    float frameHeight = this->spriteSheetSurface->h / this->_rows;

    clippingFrame->x = column * frameWidth;
    clippingFrame->y = row * frameHeight;
    clippingFrame->w = frameWidth;
    clippingFrame->h = frameHeight;
}

void SpriteSheet::render(SDL_FRect *position, int frame) {
    SDL_Rect clippingRect;

    this->_updateSpriteSheetFrame(frame, &clippingRect);

    SDL_RenderCopyF(this->renderer, this->spriteSheetTexture, &clippingRect, position);
}