#include <catch2/catch.hpp>
#include <iostream>
#include <list>

#include "../../map/sector-spatial-utils.hpp"

bool listContains(std::list<std::pair<int, int>> list,
                  std::pair<int, int> item) {

  for (std::list<std::pair<int, int>>::iterator it = list.begin();
       it != list.end(); ++it) {

    if (it->first == item.first && it->second == item.second) {
      return true;
    }
  }
  return false;
}

TEST_CASE("Correctly gets the neighbours for 0,0",
          "[Map::SectorSpatialUtils::getNeighbours]") {

  std::pair<int, int> specifiedPair = std::make_pair(0, 0);
  auto sut = new SectorSpatialUtils();

  auto result = sut->getNeighbours(specifiedPair);

  REQUIRE(result.size() == 8);
  REQUIRE(listContains(result, std::make_pair<int, int>(-1, 0)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-1, 1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(0, 1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(1, 1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(1, 0)));
  REQUIRE(listContains(result, std::make_pair<int, int>(1, -1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(0, -1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-1, -1)));
}