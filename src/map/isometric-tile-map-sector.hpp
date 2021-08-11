#ifndef SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
#define SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP

#include <iostream>
#include <random>
#include <vector>
#include <SDL.h>

#include "../sprites/sprite-registry.hpp"


class IsometricTileMapSector {
private:
  std::pair<float, float> _bottomLeft;
  std::pair<float, float> _dimensions;
  std::pair<int, int> _tilesPerAxis;
  SpriteRegistry *_spriteRegistry;
  int *_tileMap;

public:
  IsometricTileMapSector(SpriteRegistry *spriteRegistry,
                         std::pair<float, float> topLeft,
                         std::pair<float, float> dimensions,
                         std::pair<float, float> tileDimensions);

  bool pointIntersects(std::pair<float, float> point);

  std::pair<float, float> getBottomLeft();

  std::pair<float, float> getDimensions();

  int getTile(int x, int y);

  std::pair<int, int> getTilesPerAxis();

  void render(SDL_Renderer *renderer, float xPosition, float yPosition);
};

#endif // SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
