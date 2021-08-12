#include "isometric-tile-map-sector.hpp"

#include "math.h"
#include "coordinate-mapper.hpp"
#include "../util/pair-operators.hpp"

IsometricTileMapSector::IsometricTileMapSector(
    SpriteRegistry *spriteRegistry, std::pair<float, float> bottomLeft,
    std::pair<float, float> dimensions,
    std::pair<float, float> tileDimensions) {

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
  return point.first >= this->_bottomLeft.first &&
         point.first <= this->_dimensions.first &&
         point.second >= this->_bottomLeft.second &&
         point.second <= this->_dimensions.second;
}

bool IsometricTileMapSector::squareIntersects(std::pair<float, float> point, std::pair<float, float> dimensions) {
  
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

void IsometricTileMapSector::render(SDL_Renderer *renderer,
                                    std::pair<int, int> screenDimensions,
                                    std::pair<int, int> cameraPosition) {

  std::pair<float, float> isoBottomLeft = this->getBottomLeft();
  std::pair<float, float> dim = this->getDimensions();
  std::pair<float, float> isoBottomLeftCent = PairOperators::addPair(
      CoordinateMapper::worldToScreen(
          cameraPosition, screenDimensions,
          std::make_pair(this->_spriteRegistry->getSprite("tank_idle_rot225")
                             ->getFrameWidth(),
                         this->_spriteRegistry->getSprite("tank_idle_rot225")
                             ->getFrameHeight())),
      isoBottomLeft);

  SDL_FRect tilePositionRect = {
      .x = 0,
      .y = isoBottomLeftCent.second,
      .w = this->_spriteRegistry->getSprite("1")->getFrameWidth(),
      .h = this->_spriteRegistry->getSprite("1")->getFrameHeight()};

  for (int y = 0; y < this->getTilesPerAxis().second; ++y) {
    for (int x = 0; x < this->getTilesPerAxis().first; ++x) {
      if (y % 2 == 0) {
        tilePositionRect.x =
            isoBottomLeftCent.first +
            (x * this->_spriteRegistry->getSprite("0")->getFrameWidth());
      } else {
        // Every other row has a negative offset of half the tile width.
        tilePositionRect.x =
            isoBottomLeftCent.first +
            (x * this->_spriteRegistry->getSprite("0")->getFrameWidth()) +
            (this->_spriteRegistry->getSprite("0")->getFrameWidth() / 2);
      }

      if (this->getTile(x, y) == 0) {
        this->_spriteRegistry->getSprite("0")->renderTick(&tilePositionRect);
      } else {
        this->_spriteRegistry->getSprite("1")->renderTick(&tilePositionRect);
      }
    }
    tilePositionRect.y -=
        (this->_spriteRegistry->getSprite("0")->getFrameHeight() / 2);
  }

  if (this->_drawBoundingBox) {
    SDL_Rect rectangleRect = {
        .x = isoBottomLeftCent.first,
        .y = isoBottomLeftCent.second,
        .w = this->getDimensions().first,
        .h = -this->getDimensions().second,
    };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rectangleRect);
  }
}
