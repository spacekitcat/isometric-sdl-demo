#include "map-sector-database-hashmap-impl.hpp"

MapSectorDatabaseHashmapImpl::MapSectorDatabaseHashmapImpl() {}

MapSectorDatabaseHashmapImpl::~MapSectorDatabaseHashmapImpl() {}

void MapSectorDatabaseHashmapImpl::put(
    std::string key, std::shared_ptr<IsometricTileMapSector> sector) {
  _map[key] = sector;
}

std::shared_ptr<IsometricTileMapSector>
MapSectorDatabaseHashmapImpl::get(std::string key) {
  return _map[key];
}