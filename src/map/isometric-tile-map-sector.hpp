#ifndef SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
#define SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP

#include <SDL.h>
#include <iostream>
#include <random>
#include <vector>

#include "../render/sdl-manager.hpp"
#include "../sprites/sprite-registry.hpp"
#include "../map/camera.hpp"
#include "../map/coordinate-mapper.hpp"
#include "../map/intersect-target.hpp"

class IsometricTileMapSector {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::shared_ptr<Camera> _camera;
  CoordinateMapper &_coordinateMapper;
  std::pair<float, float> _position;
  std::pair<float, float> _bottomLeft;
  std::pair<float, float> _dimensions;
  std::pair<int, int> _tilesPerAxis;
  bool _drawBoundingBox;
  SpriteRegistry _spriteRegistry;
  int *_tileMap;

public:
  IsometricTileMapSector(std::shared_ptr<SDLManager> sdlManager,
                         std::shared_ptr<Camera> camera,
                         SpriteRegistry &spriteRegistry,
                         CoordinateMapper &coordinateMapper,
                         std::pair<float, float> topLeft,
                         std::pair<float, float> dimensions,
                         std::pair<float, float> tileDimensions);

  ~IsometricTileMapSector();

  bool pointIntersects(std::pair<float, float> point);

  bool squareIntersects(std::pair<float, float> point,
                        std::pair<float, float> dimensions);

  bool targetIntersects(IntersectTarget *intersectTarget);

  std::pair<float, float> getBottomLeft();

  std::pair<float, float> getDimensions();

  int getTile(int x, int y);

  std::pair<int, int> getTilesPerAxis();

  void render(std::pair<int, int> screenDimensions);
};

#endif // SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
