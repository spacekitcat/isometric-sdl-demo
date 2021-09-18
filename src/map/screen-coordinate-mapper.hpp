#pragma once

#include <algorithm>
#include <iostream>

#include "../map/camera.hpp"
#include "../render/sdl-manager.hpp"
#include "../util/pair-operators.hpp"

class ScreenCoordinateMapper {
private:
  std::shared_ptr<Configuration> _configuration;
  std::shared_ptr<Camera> _camera;
  std::pair<float, float> _playerSpriteDimensions;

public:
  ScreenCoordinateMapper(std::shared_ptr<Configuration> configuration,
                         std::shared_ptr<Camera> camera);

  std::pair<float, float>
  centerInScreenSpace(std::pair<float, float> worldPosition);

  float centerInScreenSpaceX(float worldX);
  float centerInScreenSpaceY(float worldY);

  std::pair<float, float> worldToScreen(std::pair<float, float> worldPosition);
};
