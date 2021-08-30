#ifndef SDL2APPLICATION4_COORDINATE_MAPPER_HPP
#define SDL2APPLICATION4_COORDINATE_MAPPER_HPP

#include <iostream>

#include "../map/camera.hpp"
#include "../render/sdl-manager.hpp"
#include "../util/pair-operators.hpp"

class CoordinateMapper {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::shared_ptr<Camera> _camera;
  std::pair<float, float> _playerSpriteDimensions;

public:
  CoordinateMapper(std::shared_ptr<SDLManager> sdlManager,
                   std::shared_ptr<Camera> camera);

  std::pair<float, float>
  centerInScreenSpace(std::pair<float, float> worldPosition);


  std::pair<float, float>
  worldToScreen(std::pair<float, float> worldPosition);

  float worldXToScreenX(float worldX);
  float worldYToScreenY(float worldY);
};

#endif // SDL2APPLICATION4_COORDINATE_MAPPER_HPP
