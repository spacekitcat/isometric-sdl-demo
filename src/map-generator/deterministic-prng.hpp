
#pragma once

#include "../state/game-save-state.hpp"

#include <iostream>
#include <random>

class DeterministicPrng {
private:
  GameSaveState &_gameSaveState;
  std::uniform_int_distribution<int> _uniformIntegerDistribution;
  std::default_random_engine _randomEngine;

public:
  DeterministicPrng(GameSaveState &gameSaveState);
  ~DeterministicPrng();

  int generateNextRandomNumber(int min, int max);
};