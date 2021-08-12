#ifndef SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
#define SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP

#include <iostream>
#include <random>
#include <vector>
#include <SDL.h>

#include "../sprites/sprite-registry.hpp"

class IsometricTileMapSector {
private:
  std::pair<float, float> _position;
  std::pair<float, float> _bottomLeft;
  std::pair<float, float> _dimensions;
  std::pair<int, int> _tilesPerAxis;
  bool _drawBoundingBox;
  SpriteRegistry *_spriteRegistry;
  int *_tileMap;

  std::pair<float, float> addPair(std::pair<float, float> first,
                                  std::pair<float, float> second);

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

  void render(SDL_Renderer *renderer, std::pair<int, int> screenDimensions, std::pair<int, int> cameraPosition);
};

#endif // SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
