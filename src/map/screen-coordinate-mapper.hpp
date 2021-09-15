#pragma once

#include <algorithm>
#include <iostream>

#include "../map/camera.hpp"
#include "../render/sdl-manager.hpp"
#include "../util/pair-operators.hpp"

class ScreenCoordinateMapper {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::shared_ptr<Camera> _camera;
  std::pair<float, float> _playerSpriteDimensions;

public:
  ScreenCoordinateMapper(std::shared_ptr<SDLManager> sdlManager,
                         std::shared_ptr<Camera> camera);

  std::pair<float, float>
  centerInScreenSpace(std::pair<float, float> worldPosition);

  std::pair<float, float> worldToScreen(std::pair<float, float> worldPosition);

  float worldXToScreenX(float worldX);
  float worldYToScreenY(float worldY);
};
