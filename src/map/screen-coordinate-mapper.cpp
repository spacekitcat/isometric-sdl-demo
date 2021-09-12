#include "screen-coordinate-mapper.hpp"

ScreenCoordinateMapper::ScreenCoordinateMapper(
    std::shared_ptr<SDLManager> sdlManager, std::shared_ptr<Camera> camera) {
  _sdlManager = sdlManager;
  _camera = camera;
  _playerSpriteDimensions = std::make_pair(128, 128);
}

std::pair<float, float> ScreenCoordinateMapper::centerInScreenSpace(
    std::pair<float, float> worldPosition) {

  return std::make_pair<float, float>(worldXToScreenX(worldPosition.first),
                                      worldYToScreenY(worldPosition.second));
}

float ScreenCoordinateMapper::worldXToScreenX(float worldX) {
  return -worldX + (_sdlManager->getWindowDimensions().first / 2) -
         (_playerSpriteDimensions.first / 2);
}

float ScreenCoordinateMapper::worldYToScreenY(float worldY) {
  return worldY + (_sdlManager->getWindowDimensions().second / 2) -
         (_playerSpriteDimensions.second / 2);
}

std::pair<float, float>
ScreenCoordinateMapper::worldToScreen(std::pair<float, float> worldPosition) {

  return PairOperators::addPair(
      this->centerInScreenSpace(_camera->getPosition()), worldPosition);
}