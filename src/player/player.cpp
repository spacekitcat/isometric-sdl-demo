#include "player.hpp"

Player::Player() {
  _position.first = 3840;
  _position.second = 3840;
}

Player::~Player() {}

std::pair<float, float> Player::getPosition() { return _position; }

void Player::update(long int ticks) {

  float f = ticks / 1000.0;
  std::cout << f << std::endl;

  _position = PairOperators::addPair(
      _position, PairOperators::multiplyPairBy(_velocity, f));
}

void Player::setVelocity(std::pair<float, float> velocity) {
  _velocity = velocity;
}