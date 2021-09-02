#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <iostream>
#include <math.h>
#include <SDL_image.h>

#include "../render/sdl-manager.hpp"
#include "../sprites/sprite-metadata.hpp"
#include "../textures/texture-wrapper.hpp"
#include "../textures/texture-wrapper-factory.hpp"

class Sprite {
private:
  int _animationInterval;
  int _currentFrame;
  int _columns;
  int _rows;
  std::shared_ptr<SDLManager> _sdlManager;
  SDL_Surface *_spritesheetSurface;
  std::shared_ptr<TextureWrapper> _textureWrapper;
  bool _drawBoundingBox;
  
  TextureWrapperFactory &_textureWrapperFactory;

  void updateSpriteFrame(int index, SDL_Rect *clippingFrame);

  SDL_Surface *loadGameImageAsset(std::string path);

public:
  Sprite(std::shared_ptr<SDLManager> sdlManager, TextureWrapperFactory &textureWrapperFactory);

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