
#pragma once

#include <SDL.h>
#include <iomanip>
#include <iostream>

#include "../map/screen-coordinate-mapper.hpp"
#include "../player/game-object.hpp"
#include "../sprites/sprite-selector.hpp"
#include "../sprites/sprite-state.hpp"
#include "../util/pair-operators.hpp"

class Player : public GameObject {
private:
  std::pair<float, float> _position;
  std::pair<float, float> _velocity;
  SDL_FRect _renderPositioningRect;
  SpriteSelector _spriteSelector;
  ScreenCoordinateMapper &_screenCoordinateMapper;
  SpriteState _spriteState;

public:
  Player(ScreenCoordinateMapper &screenCoordinateMapper);
  ~Player();

  std::pair<float, float> getPosition();

  void update(long int ticks);

  void render();

  void setVelocity(std::pair<float, float> velocity);

  void setSpriteSelector(SpriteSelector spriteSelector);

  void setDirection(SpriteStateDirectionEnum direction);
};