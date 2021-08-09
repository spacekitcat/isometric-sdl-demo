//

#include "isometric-tile-map-sector.hpp"

IsometricTileMapSector::IsometricTileMapSector(std::pair<float, float> bottomLeft, std::pair<float, float> topRight) {
  this->_bottomLeft = bottomLeft;
  this->_topRight = topRight;
  //  auto map = new int[512][512];
//  tile_map.push_back(*new std::vector<int>(3));
//  std::random_device r;
//  std::default_random_engine e1(r());
//  std::uniform_int_distribution<int> uniform_dist(0, 2);
//  for (int i = 0; i < 512; ++i) {
//    for (int j = 0; j < 512; ++j) {
//      map[i][j] = uniform_dist(e1);
//    }
//  }
}

bool IsometricTileMapSector::pointIntersects(std::pair<float, float> point) {
  // return point.first >= this->_bottomLeft.first && point.first <= this->_topLeft.first &&
  //        point.second >= this->_topLeft.second && point.second <= this->_topLeft.second;

  return
    point.first >= this->_bottomLeft.first && 
    point.first <= this->_topRight.first &&
    point.second >= this->_bottomLeft.second &&
    point.second <= this->_topRight.second;
}
