#include "game-save-state.hpp"

GameSaveState::GameSaveState(SpriteRegistry &spriteRegistry)
    : _spriteRegistry(spriteRegistry) {
  _gameSeed = -9005010;
  _renderVisibilityDistance = 400;

  //   _sectorDimensions = std::make_pair(256, 128);
  // _sectorDimensions = std::make_pair(512, 256);
  //   _sectorDimensions = std::make_pair(768, 384);
  //   _sectorDimensions = std::make_pair(1024, 512);
  //   _sectorDimensions = std::make_pair(1280, 640);
  //   _sectorDimensions = std::make_pair(1536, 768);
  //   _sectorDimensions = std::make_pair(1792, 896);
  //   _sectorDimensions = std::make_pair(2048, 1024);
  //   _sectorDimensions = std::make_pair(2304, 1152);

  _sectorDimensions = std::make_pair(768, 768);
  _tileDimensions = std::make_pair(256, 128);

  /*
    The sector sectorDimensions should be perfectly divisible by the
    tile sectorDimensions. Why?

    Because this map model is isometric, every odd row must have a
    an offset of _tileDimensions.first / 2 for it to align
    correctly with the even rows above and below it.

    Again owing to the isometric map model, opposite sides (North to
    South, East to West) must be even where the other is odd.

    The sector generation code will generate a tile for any position
    beginning inside a sector, it doesn't care if tiles overflow
    beyond the sector boundary. In the example below, the sector
    boundary is the same as one tile.

    (_sectorDimensions.first / _tileDimensions.first == 1)
    (_sectorDimensions.first % _tileDimensions.first == 0)

    The result is that one even and one odd row will be rendered
    and the odd row will overflow on the North and East sides.

    When more sectors are added to any of the four faces (North,
    East, South and West), the tiles will align perfectly.

    Think of how Jigsaws or Laminate Flooring work! (moreso the latter)
*/
  assert(fmod(_sectorDimensions.first, _tileDimensions.first) == 0);
  assert(fmod(_sectorDimensions.second, _tileDimensions.second) == 0);
}

GameSaveState::~GameSaveState() {}

int GameSaveState::getGameSeed() { return _gameSeed; }

std::pair<float, float> GameSaveState::getSectorDimensions() {
  return _sectorDimensions;
}

std::pair<float, float> GameSaveState::getTileDimensions() {
  return _tileDimensions;
}

int GameSaveState::getRenderVisibilityDistance() {
  return _renderVisibilityDistance;
}