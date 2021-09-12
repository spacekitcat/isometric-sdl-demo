#pragma once

#include <iostream>

#include "../config/configuration.hpp"

class WorldToMapSectorIndex {
private:
  Configuration &_configuration;

public:
  WorldToMapSectorIndex(Configuration &configuration);
  ~WorldToMapSectorIndex();

  std::pair<long int, long int>
  getMapIndex(std::pair<float, float> worldPosition);
};