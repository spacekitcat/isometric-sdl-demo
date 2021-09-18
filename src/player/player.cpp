#include "player.hpp"

Player::Player(ScreenCoordinateMapper &screenCoordinateMapper)
    : _screenCoordinateMapper(screenCoordinateMapper) {
  _position.first = 0;
  _position.second = 0;
}

Player::~Player() {}

std::pair<float, float> Player::getPosition() { return _position; }

void Player::update(long int ticks) {
  float f = ticks / 1000.0;

  _position = PairOperators::addPair(
      _position, PairOperators::multiplyPairBy(_velocity, f));

  _renderPositioningRect.x = _screenCoordinateMapper.centerInScreenSpaceX(0);
  _renderPositioningRect.y = _screenCoordinateMapper.centerInScreenSpaceY(0);

  // TODO: Move width heigh literal into config
  _renderPositioningRect.w = 256;
  _renderPositioningRect.h = 256;
}

void Player::render(SpriteState &spriteState) {
  std::shared_ptr<Sprite> playerSprite =
      _spriteSelector.selectSprite(spriteState);
  if (playerSprite != NULL) {
    playerSprite->renderTick(&_renderPositioningRect);
  }
}

void Player::setVelocity(std::pair<float, float> velocity) {
  _velocity = velocity;
}

void Player::setSpriteSelector(SpriteSelector spriteSelector) {
  _spriteSelector = spriteSelector;
}
