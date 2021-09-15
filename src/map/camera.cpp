#include "camera.hpp"

Camera::Camera(std::shared_ptr<SDLManager> sdlManager)
    : _sdlManager(sdlManager) {
  _targetPlayer = NULL;
  _zoom = .25;
}

Camera::~Camera() {}

std::pair<float, float> Camera::getPosition() { return _position; }

void Camera::setPosition(std::pair<float, float> position) {}

void Camera::setTarget(Player *player) {
  _targetPlayer = player;
  _position = _targetPlayer->getPosition();
}

void Camera::update(long int ticks) {
  if (_targetPlayer != NULL) {
    _position = _targetPlayer->getPosition();
  }
}

float Camera::getZoom() { return _zoom; }
