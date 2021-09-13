#include "sector-index-hash-map.hpp"

SectorIndexHashMap::SectorIndexHashMap() {}

SectorIndexHashMap::~SectorIndexHashMap() {}

void SectorIndexHashMap::put(std::string key,
                             std::shared_ptr<IsometricTileMapSector> sector) {
  _map[key] = sector;
}

std::shared_ptr<IsometricTileMapSector>
SectorIndexHashMap::get(std::string key) {
  return _map[key];
}