#include "camera.hpp"

Camera::Camera() {
  _targetGameObject = NULL;
  _zoom = .5;
}

Camera::~Camera() {}

std::pair<float, float> Camera::getPosition() { return _position; }

void Camera::setPosition(std::pair<float, float> position) {}

void Camera::setTarget(std::shared_ptr<GameObject> gameObject) {
  _targetGameObject = gameObject;
  _position = _targetGameObject->getPosition();
}

void Camera::update(long int ticks) {
  if (_targetGameObject != NULL) {
    _position = _targetGameObject->getPosition();
  }
}

float Camera::getZoom() const { return _zoom; }

void Camera::setZoom(float zoom) {
  _zoom = std::max(0.4f, std::min(zoom, 1.0f));
}
