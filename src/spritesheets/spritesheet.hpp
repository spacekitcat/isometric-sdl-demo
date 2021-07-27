#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SDL.h>

class SpriteSheet {
    private:
        SDL_Renderer *renderer;
        SDL_Surface *spriteSheetSurface;
        SDL_Texture *spriteSheetTexture;

        void _updateSpriteSheetFrame(int index, SDL_Surface *spriteSheet, SDL_Rect *clippingFrame);

    public:
        SpriteSheet(SDL_Renderer *renderer, SDL_Surface *spriteSheetSurface, int columns, int rows);

        ~SpriteSheet();

        void render(SDL_FRect *position, int frame);
};

#endif