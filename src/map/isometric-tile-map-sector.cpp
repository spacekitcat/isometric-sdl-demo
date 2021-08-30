#include "isometric-tile-map-sector.hpp"

#include "../util/pair-operators.hpp"
#include "coordinate-mapper.hpp"
#include "math.h"

IsometricTileMapSector::IsometricTileMapSector(
    std::shared_ptr<SDLManager> sdlManager, std::shared_ptr<Camera> camera,
    SpriteRegistry &spriteRegistry, CoordinateMapper &coordinateMapper,
    TextRenderer &textRenderer, std::pair<float, float> bottomLeft,
    std::pair<float, float> sectorDimensions)
    : _coordinateMapper(coordinateMapper), _textRenderer(textRenderer) {

  _sdlManager = sdlManager;
  _camera = camera;

  _spriteRegistry = spriteRegistry;
  _bottomLeft = bottomLeft;
  _sectorDimensions = sectorDimensions;
  _drawBoundingBox = true;

  // TODO: Little less hacking please!
  Sprite *sample_tile = _spriteRegistry.getSprite("0");

  /*  The sector sectorDimensions should be perfectly divisable by the 
      tile sectorDimensions. Why?
      
      Because this map model is isometric, every odd row must have a
      an offset of sample_tile->getFrameWidth() / 2 for it to align
      correctly with the even rows above and below it.

      Again owing to the isometric map model, opposite sides (North to
      South, East to West) must be even where the other is odd.

      The sector generation code will generate a tile for any position
      beginning inside a sector, it doesn't care if tiles overflow
      beyond the sector boundary. In the example below, the sector
      boundary is the same as one tile. 

      (_sectorDimensions.first / sample_tile->getFrameWidth() == 1)
      (_sectorDimensions.first % sample_tile->getFrameWidth() == 0)
      
      The result is that one even and one odd row will be rendered
      and the odd row will overflow on the North and East sides.

      When more sectors are added to any of the four faces (North, 
      East, South and West), the tiles will align perfectly. 
      Like laminate flooring!
  */
  assert(fmod(_sectorDimensions.first, sample_tile->getFrameWidth()) == 0);
  assert(fmod(_sectorDimensions.second, sample_tile->getFrameHeight()) == 0);

  _tilesPerAxis = std::make_pair(
      round(sectorDimensions.first / sample_tile->getFrameWidth()),
      round(sectorDimensions.second / (sample_tile->getFrameHeight() / 2)));
  _tileMap = new int[_tilesPerAxis.first * _tilesPerAxis.second];
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(0, 1);
  for (int y = 0; y < _tilesPerAxis.second; y++) {
    for (int x = 0; x < _tilesPerAxis.first; x++) {
      _tileMap[y * _tilesPerAxis.first + x] = uniform_dist(e1);
    }
  }
}

bool IsometricTileMapSector::pointIntersects(std::pair<float, float> point) {
  float padding = 200;

  return point.first >= _bottomLeft.first - padding &&
         point.first <= _bottomLeft.first + _sectorDimensions.first + padding &&
         point.second >= -(_bottomLeft.second + padding) &&
         point.second <= -_bottomLeft.second + _sectorDimensions.second + padding;
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
    SDL_SetRenderDrawColor(_sdlManager->getRenderer(), 0, 255, 0, 255);
    SDL_RenderDrawRect(_sdlManager->getRenderer(), &rectangleRect);
    _textRenderer.renderText(
        str(boost::format("%1$+5d%2$+5d") % round(getBottomLeft().first) %
            round(getBottomLeft().second)),
        _coordinateMapper.worldToScreen(getBottomLeft()));
  }
}

bool IsometricTileMapSector::targetIntersects(
    IntersectTarget *intersectTarget) {
  return false;
}

bool IsometricTileMapSector::isVisible() { 
  return this->pointIntersects(_camera->getPosition());
}