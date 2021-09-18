#pragma once

#include <iostream>

#include "../map/camera-target.hpp"
#include "../map/camera.hpp"
#include "../util/pair-operators.hpp"

class Camera {
private:
  std::pair<float, float> _position;
  float _zoom;
  CameraTarget *_targetPlayer;

public:
  Camera();

  ~Camera();

  std::pair<float, float> getPosition();

  void setPosition(std::pair<float, float> position);

  float getZoom();

  void setZoom(float zoom);

  void setTarget(CameraTarget *player);

  void update(long int ticks);
};
