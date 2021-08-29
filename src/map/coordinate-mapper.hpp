#ifndef SDL2APPLICATION4_COORDINATE_MAPPER_HPP
#define SDL2APPLICATION4_COORDINATE_MAPPER_HPP

#include <iostream>

#include "../map/camera.hpp"
#include "../render/sdl-manager.hpp"

class CoordinateMapper {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::shared_ptr<Camera> _camera;
  std::pair<float, float> _playerSpriteDimensions;

public:
  CoordinateMapper(std::shared_ptr<SDLManager> sdlManager,
                   std::shared_ptr<Camera> camera);

  std::pair<float, float>
  fromWorldToScreen(std::pair<float, float> worldPosition);

  float fromWorldXToScreenX(float worldX);
  float fromWorldYToScreenY(float worldY);
};

#endif // SDL2APPLICATION4_COORDINATE_MAPPER_HPP
