#include "isometric-tile-map-sector.hpp"

IsometricTileMapSector::IsometricTileMapSector(
    std::pair<int, int> sectorIndex, std::shared_ptr<SDLManager> sdlManager,
    std::shared_ptr<Camera> camera,
    std::shared_ptr<SpriteRegistry> spriteRegistry,
    ScreenCoordinateMapper &ScreenCoordinateMapper, TextRenderer &textRenderer,
    std::pair<float, float> bottomLeft, GameSaveState &gameSaveState,
    std::shared_ptr<DeterministicPrng> deterministicPrng,
    std::shared_ptr<Configuration> configuration)
    : _ScreenCoordinateMapper(ScreenCoordinateMapper),
      _textRenderer(textRenderer), _gameSaveState(gameSaveState),
      _deterministicPrng(deterministicPrng), _configuration(configuration),
      _spriteRegistry(spriteRegistry) {

  _sectorIndex = sectorIndex;
  _sdlManager = sdlManager;
  _camera = camera;

  _bottomLeft = bottomLeft;
  _sectorDimensions = _configuration->getSectorDimensions();
  _drawBoundingBox = true;

  _tilesPerAxis = std::make_pair(
      round(_sectorDimensions.first /
            _configuration->getTileDimensions().first),
      round(_sectorDimensions.second /
                (_configuration->getTileDimensions().second / 2) +
            1));
  _tileMap = new int[_tilesPerAxis.first * _tilesPerAxis.second];

  const double frequency = 0.4;
  const double fx = _tilesPerAxis.first / frequency;
  const double fy = _tilesPerAxis.second / frequency;
  const double octaves = 2;

  const siv::PerlinNoise perlin(_gameSaveState.getGameSeed());
  for (int y = 0; y < _tilesPerAxis.second; y++) {
    for (int x = 0; x < _tilesPerAxis.first; x++) {
      // TODO: Centralise this upper bound. I'm think about the best
      // architecture for making that info available
      // int rnd = _deterministicPrng->generateNextRandomNumber(0, 2);
      // _tileMap[y * _tilesPerAxis.first + x] = rnd;
      double perlinSample = perlin.accumulatedOctaveNoise2D_0_1(
          ((_sectorIndex.first * _tilesPerAxis.first) + x) / fx,
          ((_sectorIndex.second * _tilesPerAxis.second) + y) / fy, octaves);

      if (perlinSample < 0.2) {
        // WATER 1.
        _tileMap[y * _tilesPerAxis.first + x] = 2;
      } else if (perlinSample < 0.25) {
        // WATER 2.
        _tileMap[y * _tilesPerAxis.first + x] = 3;
      } else if (perlinSample < 0.35) {
        // WATER 3.
        _tileMap[y * _tilesPerAxis.first + x] = 2;
      } else if (perlinSample > 0.8) {
        // DOLLA DOLLA DOLLA
        _tileMap[y * _tilesPerAxis.first + x] = 4;
      } else {
        // DESERT.
        _tileMap[y * _tilesPerAxis.first + x] = 1;
      }
    }
  }
}

IsometricTileMapSector::~IsometricTileMapSector() {}

std::pair<float, float> IsometricTileMapSector::getBottomLeft() {
  return _bottomLeft;
}

std::pair<float, float> IsometricTileMapSector::getDimensions() {
  return _sectorDimensions;
}

int IsometricTileMapSector::getTile(int x, int y) {
  return _tileMap[y * _tilesPerAxis.first + x];
}

std::pair<int, int> IsometricTileMapSector::getTilesPerAxis() {
  return _tilesPerAxis;
}

void IsometricTileMapSector::render(std::pair<int, int> screenDimensions) {

  std::pair<float, float> dim = getDimensions();
  std::pair<float, float> bottomLeftPointScreenCoords =
      _ScreenCoordinateMapper.worldToScreen(getBottomLeft());

  SDL_FRect tilePositionRect = {.x = 0,
                                .y = 0,
                                .w = _configuration->getTileDimensions().first,
                                .h =
                                    _configuration->getTileDimensions().second};

  for (int y = 0; y < getTilesPerAxis().second; ++y) {
    int xOffset = 0;
    if (y % 2 == 0) {
      xOffset = _configuration->getTileDimensions().first / 2;
    }
    for (int x = 0; x < getTilesPerAxis().first; ++x) {
      tilePositionRect.x = bottomLeftPointScreenCoords.first +
                           (x * _configuration->getTileDimensions().first) +
                           xOffset;

      // TODO: Check the tile id exists.
      _spriteRegistry->getSprite(std::to_string(getTile(x, y)))
          ->renderTick(&tilePositionRect);
    }
    tilePositionRect.y = bottomLeftPointScreenCoords.second -
                         (y * (_configuration->getTileDimensions().second / 2));
  }

  if (_drawBoundingBox) {
    SDL_Rect rectangleRect = {
        .x = bottomLeftPointScreenCoords.first,
        .y = bottomLeftPointScreenCoords.second,
        .w = getDimensions().first,
        .h = getDimensions().second,
    };
    if (_configuration->getIsDebugMode()) {
      SDL_SetRenderDrawColor(_sdlManager->getRenderer(), 0, 255, 0, 255);
      SDL_RenderDrawRect(_sdlManager->getRenderer(), &rectangleRect);

      _textRenderer.renderText(
          str(boost::format("%1$+5d%2$+5d") % round(getBottomLeft().first) %
              round(getBottomLeft().second)),
          _ScreenCoordinateMapper.worldToScreen(getBottomLeft()));
    }
  }
}