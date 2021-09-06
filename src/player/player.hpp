
#pragma once

#include "../util/pair-operators.hpp"
#include <iomanip>
#include <iostream>

class Player {
private:
  std::pair<float, float> _position;
  std::pair<float, float> _velocity;

public:
  Player();
  ~Player();

  std::pair<float, float> getPosition();

  void update(long int ticks);

  void setVelocity(std::pair<float, float> velocity);
};