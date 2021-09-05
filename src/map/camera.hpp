#pragma once

#include <iostream>

class Camera {
private:
  std::pair<float, float> _position;

public:
  std::pair<float, float> getPosition();

  void applyDelta(std::pair<float, float> delta);
};
