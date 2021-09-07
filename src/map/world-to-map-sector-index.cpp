#include "world-to-map-sector-index.hpp"

WorldToMapSectorIndex::WorldToMapSectorIndex(Configuration &configuration)
    : _configuration(configuration) {}

WorldToMapSectorIndex::~WorldToMapSectorIndex() {}

std::pair<long int, long int>
WorldToMapSectorIndex::getMapIndex(std::pair<float, float> worldPosition) {

  long int xIndex = 0;
  if (worldPosition.first != 0) {
    xIndex = worldPosition.first / _configuration.getSectorDimensions().first;
  }

  long int yIndex = 0;
  if (worldPosition.second != 0) {
    yIndex = worldPosition.second / _configuration.getSectorDimensions().second;
  }

  return std::make_pair(xIndex, yIndex);
}