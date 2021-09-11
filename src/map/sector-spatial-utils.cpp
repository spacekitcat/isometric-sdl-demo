#include "sector-spatial-utils.hpp"

SectorSpatialUtils::SectorSpatialUtils() {}

SectorSpatialUtils::~SectorSpatialUtils() {}

std::string
SectorSpatialUtils::fromIntegerPairToKey(std::pair<int, int> integerPair) {
  return str(boost::format("%1%,%2%") % integerPair.first % integerPair.second);
}

std::pair<int, int> SectorSpatialUtils::fromKeyToIntegerPair(std::string key) {
  return std::make_pair<int, int>(0, 0);
}