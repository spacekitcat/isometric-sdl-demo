#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <iostream>
#include <math.h>
#include "../render/sdl-manager.hpp"
#include "./sprite-metadata.hpp"

class Sprite {
private:
  int _animationInterval;
  int _currentFrame;
  int _columns;
  int _rows;
  std::shared_ptr<SDLManager> _sdlManager;
  SDL_Surface *_spritesheetSurface;
  SDL_Texture *_spritesheetTexture;

  void updateSpriteFrame(int index, SDL_Rect *clippingFrame);

  SDL_Surface *loadGameImageAsset(std::string path);

public:
  Sprite(std::shared_ptr<SDLManager> sdlManager, std::string spritesheetPath, struct SpriteMetadata *spritesheetMetadata);

  ~Sprite();

  void setSpriteSheet(std::string spriteSheetPath, struct SpriteMetadata *metadata);

  void render(float xPosition, float yPosition, int frame);

  void renderTick(SDL_FRect *position);

  int getFrameCount();

  int getColumnCount();

  int getRowCount();

  float getFrameWidth();

  float getFrameHeight();
};

#endif