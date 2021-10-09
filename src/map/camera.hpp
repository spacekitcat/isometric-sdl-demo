#pragma once

#include <iostream>

#include "../map/camera.hpp"
#include "../player/game-object.hpp"
#include "../util/pair-operators.hpp"

class Camera {
private:
  std::pair<float, float> _position;
  float _zoom;
  std::shared_ptr<GameObject> _targetGameObject;

public:
  Camera();

  ~Camera();

  std::pair<float, float> getPosition();

  void setPosition(std::pair<float, float> position);

  float getZoom() const;

  void setZoom(float zoom);

  void setTarget(std::shared_ptr<GameObject> gameObject);

  void update(long int ticks);
};
