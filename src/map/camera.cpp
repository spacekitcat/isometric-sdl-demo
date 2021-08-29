#include "camera.hpp"
#include "../util/pair-operators.hpp"

std::pair<float, float> Camera::getPosition() {
    return _position;
}

void Camera::applyDelta(std::pair<float, float> delta) {
    _position = PairOperators::addPair(_position, delta);
}
