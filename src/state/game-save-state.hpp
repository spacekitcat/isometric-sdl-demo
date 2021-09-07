#pragma once

#include <iostream>

#include "../src/sprites/sprite-registry.hpp"

class GameSaveState {
private:
  int _gameSeed;
  int _renderVisibilityDistance;
  SpriteRegistry _spriteRegistry;

public:
  GameSaveState(SpriteRegistry &spriteRegistry);
  ~GameSaveState();
  int getGameSeed();
  int getRenderVisibilityDistance();
};
