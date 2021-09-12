#pragma once

#include <SDL.h>

#include "../config/configuration.hpp"
#include "../map-generator/deterministic-prng.hpp"
#include "../map/camera.hpp"
#include "../map/screen-coordinate-mapper.hpp"
#include "../render/sdl-manager.hpp"
#include "../sprites/sprite-registry.hpp"
#include "../state/game-save-state.hpp"
#include "../text/text-renderer.hpp"

class IsometricTileMapSector {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::shared_ptr<Camera> _camera;
  std::shared_ptr<DeterministicPrng> _deterministicPrng;
  std::shared_ptr<Configuration> _configuration;
  ScreenCoordinateMapper &_ScreenCoordinateMapper;
  TextRenderer &_textRenderer;
  std::pair<float, float> _position;
  std::pair<float, float> _bottomLeft;
  std::pair<float, float> _sectorDimensions;
  std::pair<int, int> _tilesPerAxis;
  bool _drawBoundingBox;
  SpriteRegistry _spriteRegistry;
  GameSaveState &_gameSaveState;
  int *_tileMap;

public:
  IsometricTileMapSector(std::shared_ptr<SDLManager> sdlManager,
                         std::shared_ptr<Camera> camera,
                         SpriteRegistry &spriteRegistry,
                         ScreenCoordinateMapper &ScreenCoordinateMapper,
                         TextRenderer &textRenderer,
                         std::pair<float, float> topLeft,
                         GameSaveState &gameSaveState,
                         std::shared_ptr<DeterministicPrng> deterministicPrng,
                         std::shared_ptr<Configuration> configuration);

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
