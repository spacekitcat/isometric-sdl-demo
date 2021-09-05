#pragma once

#include <iostream>

#include "../src/sprites/sprite-registry.hpp"

class GameSaveState {
private:
  int _gameSeed;
  int _renderVisibilityDistance;
  std::pair<float, float> _sectorDimensions;
  std::pair<float, float> _tileDimensions;
  SpriteRegistry _spriteRegistry;

public:
  GameSaveState(SpriteRegistry &spriteRegistry);
  ~GameSaveState();
  int getGameSeed();
  std::pair<float, float> getSectorDimensions();
  std::pair<float, float> getTileDimensions();
  int getRenderVisibilityDistance();
};
