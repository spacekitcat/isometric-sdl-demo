
#pragma once

#include "../state/game-save-state.hpp"

class DeterministicPrng {
private:
  GameSaveState _gameSaveState;

public:
  DeterministicPrng(GameSaveState &gameSaveState);
  ~DeterministicPrng();
};