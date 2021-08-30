#ifndef SDL2APPLICATION4_GAME_SAVE_STATE_HPP
#define SDL2APPLICATION4_GAME_SAVE_STATE_HPP

#include <iostream>

#include "../src/sprites/sprite-registry.hpp"

class GameSaveState {
private:
  int _gameSeed;
  std::pair<float, float> _sectorDimensions;
  std::pair<float, float> _tileDimensions;
  SpriteRegistry _spriteRegistry;

public:
  GameSaveState(SpriteRegistry &spriteRegistry);
  ~GameSaveState();
  int getGameSeed();
  std::pair<float, float> getSectorDimensions();
  std::pair<float, float> getTileDimensions();
};

#endif // SDL2APPLICATION4_GAME_SAVE_STATE_HPP
