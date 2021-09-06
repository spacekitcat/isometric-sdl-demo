#pragma once

#include <iostream>

#include "../player/player.hpp"

class Camera {
private:
  std::pair<float, float> _position;
  Player *_targetPlayer;

public:
  Camera();

  ~Camera();

  std::pair<float, float> getPosition();

  void setPosition(std::pair<float, float> position);

  void setTarget(Player *player);

  void update(long int ticks);
};
