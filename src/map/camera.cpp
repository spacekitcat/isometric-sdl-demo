#include "camera.hpp"
#include "../util/pair-operators.hpp"

Camera::Camera() { _targetPlayer = NULL; }

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
