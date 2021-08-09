#ifndef SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
#define SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP

#include <iostream>
#include <random>
#include <vector>

class IsometricTileMapSector {
private:
  std::pair<float, float> _bottomLeft;
  std::pair<float, float> _topRight;

  std::vector< std::vector<int> > tile_map;

public:
  IsometricTileMapSector(std::pair<float, float> topLeft, std::pair<float, float> bottomLeft);

  bool pointIntersects(std::pair<float, float> point);
};


#endif //SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
