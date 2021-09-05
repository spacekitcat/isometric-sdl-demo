#include "deterministic-prng.hpp"

DeterministicPrng::DeterministicPrng(GameSaveState &gameSaveState)
    : _gameSaveState(gameSaveState) {}

DeterministicPrng::~DeterministicPrng() {}