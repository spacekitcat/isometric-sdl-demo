
#pragma once

#include <iostream>

#include "../map/isometric-tile-map-sector.hpp"
#include "../map/map-sector-database.hpp"

class SectorIndexHashMap : public SectorIndex {
private:
  std::map<std::string, std::shared_ptr<IsometricTileMapSector>> _map;

public:
  SectorIndexHashMap();
  ~SectorIndexHashMap();
  void put(std::string key, std::shared_ptr<IsometricTileMapSector> sector);

  std::shared_ptr<IsometricTileMapSector> get(std::string key);
};