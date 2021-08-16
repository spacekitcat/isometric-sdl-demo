#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <iostream>
#include <math.h>
#include "../render/sdl-manager.hpp"

class Sprite {
private:
  int _animationInterval;
  int _currentFrame;
  int _columns;
  int _rows;
  std::shared_ptr<SDLManager> _sdlManager;
  SDL_Surface *spriteSheetSurface;
  SDL_Texture *spriteSheetTexture;

  void _updateSpriteFrame(int index, SDL_Rect *clippingFrame);

  SDL_Surface *loadGameImageAsset(std::string path);

public:
  Sprite(std::shared_ptr<SDLManager> sdlManager, std::string spriteSheetPath, int column,
         int rows);

  ~Sprite();

  void render(float xPosition, float yPosition, int frame);

  void renderTick(SDL_FRect *position);

  int getFrameCount();

  int getColumnCount();

  int getRowCount();

  float getFrameWidth();

  float getFrameHeight();
};

#endif