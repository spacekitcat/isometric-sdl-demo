#include "game-save-state.hpp"

GameSaveState::GameSaveState(std::shared_ptr<SpriteRegistry> spriteRegistry)
    : _spriteRegistry(spriteRegistry) {
  _gameSeed = -7001912;
  _renderVisibilityDistance = 2400;
}

GameSaveState::~GameSaveState() {}

int GameSaveState::getGameSeed() { return _gameSeed; }

int GameSaveState::getRenderVisibilityDistance() {
  return _renderVisibilityDistance;
}