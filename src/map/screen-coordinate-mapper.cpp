#include "screen-coordinate-mapper.hpp"

ScreenCoordinateMapper::ScreenCoordinateMapper(
    std::shared_ptr<Configuration> configuration,
    std::shared_ptr<Camera> camera)
    : _configuration(configuration) {
  _camera = camera;
}

std::pair<float, float> ScreenCoordinateMapper::centerInScreenSpace(
    std::pair<float, float> screenPosition) {

  return std::make_pair<float, float>(
      centerInScreenSpaceX(screenPosition.first),
      centerInScreenSpaceY(screenPosition.second));
}

float ScreenCoordinateMapper::centerInScreenSpaceX(float screenPositionX) {
  return screenPositionX + ((_configuration->getWindowDimensions().first / 2)) /
                               _camera->getZoom();
}

float ScreenCoordinateMapper::centerInScreenSpaceY(float screenPositionY) {
  return screenPositionY +
         ((_configuration->getWindowDimensions().second / 2)) /
             _camera->getZoom();
}

std::pair<float, float>
ScreenCoordinateMapper::worldToScreen(std::pair<float, float> worldPosition) {
  return this->centerInScreenSpace(
      std::make_pair(worldPosition.first - _camera->getPosition().first,
                     worldPosition.second + _camera->getPosition().second));
}