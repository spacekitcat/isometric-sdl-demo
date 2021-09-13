
#pragma once

#include <iostream>

#include "../map/isometric-tile-map-sector.hpp"
#include "../map/map-sector-database.hpp"

class MapSectorDatabaseHashmapImpl : public MapSectorDatabase {
private:
  std::map<std::string, std::shared_ptr<IsometricTileMapSector>> _map;

public:
  MapSectorDatabaseHashmapImpl();
  ~MapSectorDatabaseHashmapImpl();
  void put(std::string key, std::shared_ptr<IsometricTileMapSector> sector);

  std::shared_ptr<IsometricTileMapSector> get(std::string key);
};