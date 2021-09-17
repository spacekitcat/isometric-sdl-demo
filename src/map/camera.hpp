#pragma once

#include <iostream>

#include "../map/camera-target.hpp"
#include "../map/camera.hpp"
#include "../render/sdl-manager.hpp"
#include "../util/pair-operators.hpp"

class Camera {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::pair<float, float> _position;
  float _zoom;
  CameraTarget *_targetPlayer;

public:
  Camera(std::shared_ptr<SDLManager> sdlManager);

  ~Camera();

  std::pair<float, float> getPosition();

  void setPosition(std::pair<float, float> position);

  float getZoom();

  void setZoom(float zoom);

  void setTarget(CameraTarget *player);

  void update(long int ticks);
};
