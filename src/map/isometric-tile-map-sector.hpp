#ifndef SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
#define SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP

#include <iostream>
#include <random>
#include <vector>

class IsometricTileMapSector {
private:
  std::pair<float, float> _bottomLeft;
  std::pair<float, float> _dimensions;
  std::pair<int, int> _tilesPerAxis;
  int *_tileMap;

public:
  IsometricTileMapSector(std::pair<float, float> topLeft,
                         std::pair<float, float> dimensions,
                         std::pair<float, float> tileDimensions);

  bool pointIntersects(std::pair<float, float> point);

  std::pair<float, float> getBottomLeft();

  std::pair<float, float> getDimensions();

  int getTile(int x, int y);

  std::pair<int, int> getTilesPerAxis();
};

#endif // SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
