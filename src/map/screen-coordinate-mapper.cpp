#include "screen-coordinate-mapper.hpp"

ScreenCoordinateMapper::ScreenCoordinateMapper(
    std::shared_ptr<Configuration> configuration,
    std::shared_ptr<Camera> camera)
    : _configuration(configuration) {
  _camera = camera;
  _playerSpriteDimensions = std::make_pair(128, 128);
}

std::pair<float, float> ScreenCoordinateMapper::centerInScreenSpace(
    std::pair<float, float> worldPosition) {

  return std::make_pair<float, float>(
      centerInScreenSpaceX(worldPosition.first),
      centerInScreenSpaceY(worldPosition.second));
}

float ScreenCoordinateMapper::centerInScreenSpaceX(float worldX) {
  return -worldX + ((_configuration->getWindowDimensions().first / 2) -
                    (_playerSpriteDimensions.first / 2)) *
                       1 / _camera->getZoom();
}

float ScreenCoordinateMapper::centerInScreenSpaceY(float worldY) {
  return worldY + ((_configuration->getWindowDimensions().second / 2) -
                   (_playerSpriteDimensions.second / 2)) *
                      1 / _camera->getZoom();
}

std::pair<float, float>
ScreenCoordinateMapper::worldToScreen(std::pair<float, float> worldPosition) {

  return PairOperators::addPair(
      this->centerInScreenSpace(_camera->getPosition()), worldPosition);
}