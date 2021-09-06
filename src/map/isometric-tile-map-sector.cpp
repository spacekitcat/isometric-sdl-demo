#include "isometric-tile-map-sector.hpp"
#include "../util/pair-operators.hpp"
#include "coordinate-mapper.hpp"

IsometricTileMapSector::IsometricTileMapSector(
    std::shared_ptr<SDLManager> sdlManager, std::shared_ptr<Camera> camera,
    SpriteRegistry &spriteRegistry, CoordinateMapper &coordinateMapper,
    TextRenderer &textRenderer, std::pair<float, float> bottomLeft,
    GameSaveState &gameSaveState,
    std::shared_ptr<DeterministicPrng> deterministicPrng,
    std::shared_ptr<Configuration> configuration)
    : _coordinateMapper(coordinateMapper), _textRenderer(textRenderer),
      _gameSaveState(gameSaveState), _deterministicPrng(deterministicPrng),
      _configuration(configuration) {

  _sdlManager = sdlManager;
  _camera = camera;

  _spriteRegistry = spriteRegistry;
  _bottomLeft = bottomLeft;
  _sectorDimensions = _gameSaveState.getSectorDimensions();
  _drawBoundingBox = true;

  _tilesPerAxis = std::make_pair(
      round(_sectorDimensions.first / _gameSaveState.getTileDimensions().first),
      round(_sectorDimensions.second /
            (_gameSaveState.getTileDimensions().second / 2)));
  _tileMap = new int[_tilesPerAxis.first * _tilesPerAxis.second];

  for (int y = 0; y < _tilesPerAxis.second; y++) {
    for (int x = 0; x < _tilesPerAxis.first; x++) {
      int rnd = _deterministicPrng->generateNextRandomNumber(0, 1);
      std::cout << rnd << std::endl;
      _tileMap[y * _tilesPerAxis.first + x] = rnd;
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
      _coordinateMapper.worldToScreen(getBottomLeft());

  SDL_FRect tilePositionRect = {
      .x = 0,
      .y = bottomLeftPointScreenCoords.second,
      .w = _spriteRegistry.getSprite("1")->getFrameWidth(),
      .h = _spriteRegistry.getSprite("1")->getFrameHeight()};

  for (int y = 0; y < getTilesPerAxis().second; ++y) {
    for (int x = 0; x < getTilesPerAxis().first; ++x) {
      if (y % 2 == 0) {
        tilePositionRect.x =
            bottomLeftPointScreenCoords.first +
            (x * _spriteRegistry.getSprite("0")->getFrameWidth());
      } else {
        // Every other row has a negative offset of half the tile width.
        tilePositionRect.x =
            bottomLeftPointScreenCoords.first +
            (x * _spriteRegistry.getSprite("0")->getFrameWidth()) +
            (_spriteRegistry.getSprite("0")->getFrameWidth() / 2);
      }

      if (getTile(x, y) == 0) {
        _spriteRegistry.getSprite("0")->renderTick(&tilePositionRect);
      } else {
        _spriteRegistry.getSprite("1")->renderTick(&tilePositionRect);
      }
    }
    tilePositionRect.y -=
        (_spriteRegistry.getSprite("0")->getFrameHeight() / 2);
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
          _coordinateMapper.worldToScreen(getBottomLeft()));
    }
  }
}

bool IsometricTileMapSector::isVisible() {
  return this->pointIntersects(_camera->getPosition());
}