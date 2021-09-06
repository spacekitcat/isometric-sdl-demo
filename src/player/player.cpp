#include "player.hpp"

Player::Player() {}

Player::~Player() {}

std::pair<float, float> Player::getPosition() { return _position; }

void Player::update(long int ticks) {

  float f = ticks / 1000.0;

  _position = PairOperators::addPair(
      _position, PairOperators::multiplyPairBy(_velocity, f));
}

void Player::setVelocity(std::pair<float, float> velocity) {
  _velocity = velocity;
}