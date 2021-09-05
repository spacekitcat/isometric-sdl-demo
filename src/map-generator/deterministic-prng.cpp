#include "deterministic-prng.hpp"

DeterministicPrng::DeterministicPrng(GameSaveState &gameSaveState)
    : _gameSaveState(gameSaveState) {

  _randomEngine.seed(_gameSaveState.getGameSeed());
}

DeterministicPrng::~DeterministicPrng() {}

int DeterministicPrng::generateNextRandomNumber(int min, int max) {
  std::uniform_int_distribution<int> uniform_dist(min, max);
  return uniform_dist(_randomEngine);
}