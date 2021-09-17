
#pragma once

#include <SDL.h>
#include <iomanip>
#include <iostream>

#include "../map/camera-target.hpp"
#include "../map/screen-coordinate-mapper.hpp"
#include "../sprites/sprite-selector.hpp"
#include "../util/pair-operators.hpp"

class Player : public CameraTarget {
private:
  std::pair<float, float> _position;
  std::pair<float, float> _velocity;
  SDL_FRect _renderPositioningRect;
  SpriteSelector _spriteSelector;
  ScreenCoordinateMapper &_screenCoordinateMapper;

public:
  Player(ScreenCoordinateMapper &screenCoordinateMapper);
  ~Player();

  std::pair<float, float> getPosition();

  void update(long int ticks);

  void render(SpriteState &spriteState);

  void setVelocity(std::pair<float, float> velocity);

  void setSpriteSelector(SpriteSelector spriteSelector);
};