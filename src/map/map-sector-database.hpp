
#pragma once

#include <iostream>

#include "../map/isometric-tile-map-sector.hpp"

class MapSectorDatabase {
private:
public:
  MapSectorDatabase() {}
  virtual ~MapSectorDatabase(){};

  virtual void put(std::string key,
                   std::shared_ptr<IsometricTileMapSector> sector) = 0;

  virtual std::shared_ptr<IsometricTileMapSector> get(std::string key) = 0;
};