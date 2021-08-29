#include "isometric-tile-map-sector.hpp"

#include "../util/pair-operators.hpp"
#include "coordinate-mapper.hpp"
#include "math.h"

IsometricTileMapSector::IsometricTileMapSector(
    std::shared_ptr<SDLManager> sdlManager, std::shared_ptr<Camera> camera,
    SpriteRegistry &spriteRegistry, CoordinateMapper &coordinateMapper,
    TextRenderer &textRenderer, std::pair<float, float> bottomLeft,
    std::pair<float, float> dimensions, std::pair<float, float> tileDimensions)
    : _coordinateMapper(coordinateMapper), _textRenderer(textRenderer) {
  _sdlManager = sdlManager;
  _camera = camera;

  this->_spriteRegistry = spriteRegistry;
  this->_bottomLeft = bottomLeft;
  this->_dimensions = dimensions;
  this->_drawBoundingBox = true;

  this->_tilesPerAxis =
      std::make_pair(round(dimensions.first / tileDimensions.first),
                     round(dimensions.second / (tileDimensions.second / 2)));
  this->_tileMap = new int[_tilesPerAxis.first * _tilesPerAxis.second];
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(0, 1);
  for (int y = 0; y < _tilesPerAxis.second; y++) {
    for (int x = 0; x < _tilesPerAxis.first; x++) {
      this->_tileMap[y * this->_tilesPerAxis.first + x] = uniform_dist(e1);
    }
  }
}

bool IsometricTileMapSector::pointIntersects(std::pair<float, float> point) {
  float padding = 100;

  return point.first >= _bottomLeft.first - padding &&
         point.first <= _bottomLeft.first + this->_dimensions.first + padding &&
         point.second >= -(_bottomLeft.second + padding) &&
         point.second <=
             -_bottomLeft.second + this->_dimensions.second + padding;
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

  return this->pointIntersects(bottomLeftPoint) ||
         this->pointIntersects(bottomRightPoint) ||
         this->pointIntersects(topLeftPoint) ||
         this->pointIntersects(topRightPoint);
}

std::pair<float, float> IsometricTileMapSector::getBottomLeft() {
  return this->_bottomLeft;
}

std::pair<float, float> IsometricTileMapSector::getDimensions() {
  return this->_dimensions;
}

int IsometricTileMapSector::getTile(int x, int y) {
  return this->_tileMap[y * this->_tilesPerAxis.first + x];
}

std::pair<int, int> IsometricTileMapSector::getTilesPerAxis() {
  return this->_tilesPerAxis;
}

void IsometricTileMapSector::render(std::pair<int, int> screenDimensions) {

  std::pair<float, float> dim = this->getDimensions();
  std::pair<float, float> isoBottomLeftCent =
      _coordinateMapper.fromWorldToScreenAbs(this->getBottomLeft());

  SDL_FRect tilePositionRect = {
      .x = 0,
      .y = isoBottomLeftCent.second,
      .w = this->_spriteRegistry.getSprite("1")->getFrameWidth(),
      .h = this->_spriteRegistry.getSprite("1")->getFrameHeight()};

  for (int y = 0; y < this->getTilesPerAxis().second; ++y) {
    for (int x = 0; x < this->getTilesPerAxis().first; ++x) {
      if (y % 2 == 0) {
        tilePositionRect.x =
            isoBottomLeftCent.first +
            (x * this->_spriteRegistry.getSprite("0")->getFrameWidth());
      } else {
        // Every other row has a negative offset of half the tile width.
        tilePositionRect.x =
            isoBottomLeftCent.first +
            (x * this->_spriteRegistry.getSprite("0")->getFrameWidth()) +
            (this->_spriteRegistry.getSprite("0")->getFrameWidth() / 2);
      }

      if (this->getTile(x, y) == 0) {
        this->_spriteRegistry.getSprite("0")->renderTick(&tilePositionRect);
      } else {
        this->_spriteRegistry.getSprite("1")->renderTick(&tilePositionRect);
      }
    }
    tilePositionRect.y -=
        (this->_spriteRegistry.getSprite("0")->getFrameHeight() / 2);
  }

  if (this->_drawBoundingBox) {
    SDL_Rect rectangleRect = {
        .x = isoBottomLeftCent.first,
        .y = isoBottomLeftCent.second,
        .w = this->getDimensions().first,
        .h = -this->getDimensions().second,
    };
    SDL_SetRenderDrawColor(_sdlManager->getRenderer(), 0, 255, 0, 255);
    SDL_RenderDrawRect(_sdlManager->getRenderer(), &rectangleRect);
    _textRenderer.renderText(
        str(boost::format("%1$+5d%2$+5d") %
            round(this->getBottomLeft().first) %
            round(this->getBottomLeft().second)),
        _coordinateMapper.fromWorldToScreenAbs(std::make_pair(0, 0)));
  }
}

bool IsometricTileMapSector::targetIntersects(
    IntersectTarget *intersectTarget) {
  return false;
}

bool IsometricTileMapSector::isVisible() { return true; }