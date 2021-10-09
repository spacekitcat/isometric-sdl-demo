#include "game-save-state.hpp"

GameSaveState::GameSaveState(std::shared_ptr<SpriteRegistry> spriteRegistry)
    : _spriteRegistry(spriteRegistry) {
  _gameSeed = -78434910;
  _renderVisibilityDistance = 8000;
}

GameSaveState::~GameSaveState() {}

int GameSaveState::getGameSeed() const { return _gameSeed; }

int GameSaveState::getRenderVisibilityDistance() const {
  return _renderVisibilityDistance;
}