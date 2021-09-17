#include "isometric-tile-map-sector.hpp"

IsometricTileMapSector::IsometricTileMapSector(
    std::shared_ptr<SDLManager> sdlManager, std::shared_ptr<Camera> camera,
    std::shared_ptr<SpriteRegistry> spriteRegistry,
    ScreenCoordinateMapper &ScreenCoordinateMapper, TextRenderer &textRenderer,
    std::pair<float, float> bottomLeft, GameSaveState &gameSaveState,
    std::shared_ptr<DeterministicPrng> deterministicPrng,
    std::shared_ptr<Configuration> configuration)
    : _ScreenCoordinateMapper(ScreenCoordinateMapper),
      _textRenderer(textRenderer), _gameSaveState(gameSaveState),
      _deterministicPrng(deterministicPrng), _configuration(configuration),
      _spriteRegistry(spriteRegistry) {

  _sdlManager = sdlManager;
  _camera = camera;

  _bottomLeft = bottomLeft;
  _sectorDimensions = _configuration->getSectorDimensions();
  _drawBoundingBox = true;

  _tilesPerAxis =
      std::make_pair(round(_sectorDimensions.first /
                           _configuration->getTileDimensions().first),
                     round(_sectorDimensions.second /
                           (_configuration->getTileDimensions().second / 2)));
  _tileMap = new int[_tilesPerAxis.first * _tilesPerAxis.second];

  const double frequency = 1;
  const double fx = _tilesPerAxis.first / frequency;
  const double fy = _tilesPerAxis.second / frequency;
  const double octaves = 16;

  const siv::PerlinNoise perlin(
      _deterministicPrng->generateNextRandomNumber(0, 49));
  for (int y = 0; y < _tilesPerAxis.second; y++) {
    for (int x = 0; x < _tilesPerAxis.first; x++) {
      // TODO: Centralise this upper bound. I'm think about the best
      // architecture for making that info available
      // int rnd = _deterministicPrng->generateNextRandomNumber(0, 2);
      // _tileMap[y * _tilesPerAxis.first + x] = rnd;
      double perlinSample =
          perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves);
      if (perlinSample > 0.4) {
        _tileMap[y * _tilesPerAxis.first + x] = 1;
      } else {
        _tileMap[y * _tilesPerAxis.first + x] = 2;
      }
    }
  }
}

IsometricTileMapSector::~IsometricTileMapSector() {}

bool IsometricTileMapSector::pointIntersects(std::pair<float, float> point) {
  float padding = _gameSaveState.getRenderVisibilityDistance();

  return point.first >= _bottomLeft.first - padding &&
         point.first <= _bottomLeft.first + _sectorDimensions.first + padding &&
         point.second >= -(_bottomLeft.second + padding) &&
         point.second <=
             -_bottomLeft.second + _sectorDimensions.second + padding;
}

bool IsometricTileMapSector::squareIntersects(
    std::pair<float, float> principlePoint,
    std::pair<float, float> dimensions) {

  std::pair<float, float> bottomLeftPoint =
      std::make_pair(principlePoint.first, principlePoint.second);

  std::pair<float, float> bottomRightPoint = std::make_pair(
      principlePoint.first + dimensions.first, principlePoint.second);

  std::pair<float, float> topLeftPoint = std::make_pair(
      principlePoint.first, principlePoint.second + dimensions.second);

  std::pair<float, float> topRightPoint =
      std::make_pair(principlePoint.first + dimensions.first,
                     principlePoint.second + dimensions.second);

  return pointIntersects(bottomLeftPoint) ||
         pointIntersects(bottomRightPoint) || pointIntersects(topLeftPoint) ||
         pointIntersects(topRightPoint);
}

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

  SDL_FRect tilePositionRect = {
      .x = 0,
      .y = bottomLeftPointScreenCoords.second,
      .w = _spriteRegistry->getSprite("1")->getFrameWidth(),
      .h = _spriteRegistry->getSprite("1")->getFrameHeight()};

  for (int y = 0; y < getTilesPerAxis().second; ++y) {
    for (int x = 0; x < getTilesPerAxis().first; ++x) {
      if (y % 2 == 0) {
        tilePositionRect.x =
            bottomLeftPointScreenCoords.first +
            (x * _spriteRegistry->getSprite("0")->getFrameWidth());
      } else {
        // Every other row has a negative offset of half the tile width.
        tilePositionRect.x =
            bottomLeftPointScreenCoords.first +
            (x * _spriteRegistry->getSprite("0")->getFrameWidth()) +
            (_spriteRegistry->getSprite("0")->getFrameWidth() / 2);
      }

      // TODO: Check the tile id exists.
      _spriteRegistry->getSprite(std::to_string(getTile(x, y)))
          ->renderTick(&tilePositionRect);
    }
    tilePositionRect.y -=
        (_spriteRegistry->getSprite("0")->getFrameHeight() / 2);
  }

  if (_drawBoundingBox) {
    SDL_Rect rectangleRect = {
        .x = bottomLeftPointScreenCoords.first,
        .y = bottomLeftPointScreenCoords.second,
        .w = getDimensions().first,
        .h = -getDimensions().second,
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

bool IsometricTileMapSector::isVisible() {
  return this->pointIntersects(_camera->getPosition());
}