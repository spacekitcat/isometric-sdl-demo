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
#include "../text/text-renderer.hpp"
#include "../state/game-save-state.hpp"

class IsometricTileMapSector {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::shared_ptr<Camera> _camera;
  CoordinateMapper &_coordinateMapper;
  TextRenderer &_textRenderer;
  std::pair<float, float> _position;
  std::pair<float, float> _bottomLeft;
  std::pair<float, float> _sectorDimensions;
  std::pair<int, int> _tilesPerAxis;
  bool _drawBoundingBox;
  SpriteRegistry _spriteRegistry;
  GameSaveState _gameSaveState;
  int *_tileMap;

public:
  IsometricTileMapSector(std::shared_ptr<SDLManager> sdlManager,
                         std::shared_ptr<Camera> camera,
                         SpriteRegistry &spriteRegistry,
                         CoordinateMapper &coordinateMapper,
                         TextRenderer &textRenderer,
                         std::pair<float, float> topLeft,
                         GameSaveState &gameSaveState);

  ~IsometricTileMapSector();

  bool pointIntersects(std::pair<float, float> point);

  bool squareIntersects(std::pair<float, float> point,
                        std::pair<float, float> dimensions);

  bool isVisible();

  std::pair<float, float> getBottomLeft();

  std::pair<float, float> getDimensions();

  int getTile(int x, int y);

  std::pair<int, int> getTilesPerAxis();

  void render(std::pair<int, int> screenDimensions);
};

#endif // SDL2APPLICATION4_ISOMETRIC_TILE_MAP_SECTOR_HPP
