#pragma once

#include <iostream>

#include "../src/sprites/sprite-registry.hpp"

class GameSaveState {
private:
  int _gameSeed;
  int _renderVisibilityDistance;
  std::shared_ptr<SpriteRegistry> _spriteRegistry;

public:
  GameSaveState(std::shared_ptr<SpriteRegistry> spriteRegistry);
  ~GameSaveState();
  int getGameSeed();
  int getRenderVisibilityDistance();
};
