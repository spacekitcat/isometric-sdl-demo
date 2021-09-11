#include "sector-spatial-utils.hpp"

SectorSpatialUtils::SectorSpatialUtils() {}

SectorSpatialUtils::~SectorSpatialUtils() {}

std::string
SectorSpatialUtils::fromIntegerPairToKey(std::pair<int, int> integerPair) {
  return str(boost::format("%1%,%2%") % integerPair.first % integerPair.second);
}

std::pair<int, int> SectorSpatialUtils::fromKeyToIntegerPair(std::string key) {
  std::string delimiter = ",";
  int xValue = std::stoi(key.substr(0, key.find(delimiter)));
  int yValue = std::stoi(key.substr(key.find(delimiter) + 1));

  return std::make_pair(xValue, yValue);
}

std::list<std::pair<int, int>>
SectorSpatialUtils::getNeighbours(std::pair<int, int> integerPair) {
  std::list<std::pair<int, int>> neighbours;

  neighbours.push_back(std::make_pair(-1, 0));
  neighbours.push_back(std::make_pair(-1, 1));
  neighbours.push_back(std::make_pair(0, 1));
  neighbours.push_back(std::make_pair(1, 1));
  neighbours.push_back(std::make_pair(1, 0));
  neighbours.push_back(std::make_pair(1, -1));
  neighbours.push_back(std::make_pair(0, -1));
  neighbours.push_back(std::make_pair(-1, -1));

  return neighbours;
}