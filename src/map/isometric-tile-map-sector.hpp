#ifndef SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
#define SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP

#include <SDL.h>
#include <iostream>
#include <random>
#include <vector>

#include "../sprites/sprite-registry.hpp"
#include "../render/sdl-manager.hpp"


class IsometricTileMapSector {
private:
  SDLManager *_sdlManager;
  std::pair<float, float> _position;
  std::pair<float, float> _bottomLeft;
  std::pair<float, float> _dimensions;
  std::pair<int, int> _tilesPerAxis;
  bool _drawBoundingBox;
  SpriteRegistry *_spriteRegistry;
  int *_tileMap;

public:
  IsometricTileMapSector(SDLManager *sdlManager, SpriteRegistry *spriteRegistry,
                         std::pair<float, float> topLeft,
                         std::pair<float, float> dimensions,
                         std::pair<float, float> tileDimensions);

  bool pointIntersects(std::pair<float, float> point);

  bool squareIntersects(std::pair<float, float> point,
                        std::pair<float, float> dimensions);

  std::pair<float, float> getBottomLeft();

  std::pair<float, float> getDimensions();

  int getTile(int x, int y);

  std::pair<int, int> getTilesPerAxis();

  void render(std::pair<int, int> screenDimensions,
              std::pair<int, int> cameraPosition);
};

#endif // SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
