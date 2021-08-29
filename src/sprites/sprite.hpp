#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <iostream>
#include <math.h>
#include <SDL_image.h>

#include "../render/sdl-manager.hpp"
#include "../sprites/sprite-metadata.hpp"
#include "../map/intersect-target.hpp"

class Sprite : public IntersectTarget {
private:
  int _animationInterval;
  int _currentFrame;
  int _columns;
  int _rows;
  std::shared_ptr<SDLManager> _sdlManager;
  SDL_Surface *_spritesheetSurface;
  SDL_Texture *_spritesheetTexture;
  bool _drawBoundingBox;

  void updateSpriteFrame(int index, SDL_Rect *clippingFrame);

  SDL_Surface *loadGameImageAsset(std::string path);

public:
  Sprite(std::shared_ptr<SDLManager> sdlManager);

  ~Sprite();

  void setSpritesheet(std::string spriteSheetPath, struct SpriteMetadata *metadata);

  void render(float xPosition, float yPosition, int frame);

  void renderTick(SDL_FRect *position);

  int getFrameCount();

  int getColumnCount();

  int getRowCount();

  float getFrameWidth();

  float getFrameHeight();

  void setRenderBoundingBox(bool render);

  std::pair<float, float> getDimensions();
};

#endif