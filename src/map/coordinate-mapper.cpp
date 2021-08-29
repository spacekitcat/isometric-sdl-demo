#include "coordinate-mapper.hpp"

CoordinateMapper::CoordinateMapper(std::shared_ptr<SDLManager> sdlManager,
                                   std::shared_ptr<Camera> camera) {
  _sdlManager = sdlManager;
  _camera = camera;
  _playerSpriteDimensions = std::make_pair(128, 128);
}

std::pair<float, float>
CoordinateMapper::fromWorldToScreen(std::pair<float, float> worldPosition) {

  return std::make_pair<float, float>(
      fromWorldXToScreenX(worldPosition.first),
      fromWorldYToScreenY(worldPosition.second));
}

float CoordinateMapper::fromWorldXToScreenX(float worldX) {
  return -worldX + (_sdlManager->getWindowDimensions().first / 2) -
         (_playerSpriteDimensions.first / 2);
}

float CoordinateMapper::fromWorldYToScreenY(float worldY) {
  return worldY + (_sdlManager->getWindowDimensions().second / 2) -
         (_playerSpriteDimensions.second / 2);
}