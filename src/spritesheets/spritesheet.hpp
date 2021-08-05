#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SDL.h>
#include <iostream>
#include <math.h>


class SpriteSheet {
    private:
        int _columns;
        int _rows;
        SDL_Renderer *renderer;
        SDL_Surface *spriteSheetSurface;
        SDL_Texture *spriteSheetTexture;

        void _updateSpriteSheetFrame(int index, SDL_Rect *clippingFrame);

    public:
        SpriteSheet(SDL_Renderer *renderer, SDL_Surface *spriteSheetSurface, int columns, int rows);

        ~SpriteSheet();

        void render(SDL_FRect *position, int frame);

        int getFrameCount();
        
        int getColumnCount();

        int getRowCount();

        float getFrameWidth();

        float getFrameHeight();
};

#endif