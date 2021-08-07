#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <iostream>
#include <math.h>


class Sprite  {
    private:
        int _animationInterval;
        int _currentFrame;
        int _columns;
        int _rows;
        SDL_Renderer *renderer;
        SDL_Surface *spriteSheetSurface;
        SDL_Texture *spriteSheetTexture;

        void _updateSpriteFrame(int index, SDL_Rect *clippingFrame);

    public:
        Sprite();

        Sprite(SDL_Renderer *renderer, SDL_Surface *spriteSheetSurface, int columns, int rows);

        ~Sprite();

        void render(SDL_FRect *position, int frame);

        void renderTick(SDL_FRect *position);

        int getFrameCount();
        
        int getColumnCount();

        int getRowCount();

        float getFrameWidth();

        float getFrameHeight();
};

#endif