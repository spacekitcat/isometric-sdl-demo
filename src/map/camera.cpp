#include "camera.hpp"

Camera::Camera(std::shared_ptr<SDLManager> sdlManager)
    : _sdlManager(sdlManager) {
  _targetPlayer = NULL;
  _zoom = .5;
}

Camera::~Camera() {}

std::pair<float, float> Camera::getPosition() { return _position; }

void Camera::setPosition(std::pair<float, float> position) {}

void Camera::setTarget(CameraTarget *player) {
  _targetPlayer = player;
  _position = _targetPlayer->getPosition();
}

void Camera::update(long int ticks) {
  if (_targetPlayer != NULL) {
    _position = _targetPlayer->getPosition();
  }
}

float Camera::getZoom() { return _zoom; }

void Camera::setZoom(float zoom) {
  _zoom = std::max(0.25f, std::min(zoom, 1.0f));
}
