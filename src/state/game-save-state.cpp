#include "game-save-state.hpp"

GameSaveState::GameSaveState(SpriteRegistry &spriteRegistry)
    : _spriteRegistry(spriteRegistry) {
  _gameSeed = -9005010;
  _renderVisibilityDistance = 400;
}

GameSaveState::~GameSaveState() {}

int GameSaveState::getGameSeed() { return _gameSeed; }

int GameSaveState::getRenderVisibilityDistance() {
  return _renderVisibilityDistance;
}