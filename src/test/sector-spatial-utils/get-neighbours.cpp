#include <catch2/catch.hpp>
#include <iostream>
#include <list>

#include "../../map/sector-spatial-utils.hpp"

TEST_CASE("Correctly gets the neighbours for 0,0",
          "[Map::SectorSpatialUtils::getNeighbours]") {

  std::pair<int, int> specifiedPair = std::make_pair(0, 0);
  auto sut = new SectorSpatialUtils();

  auto result = sut->getNeighbours(specifiedPair);
  REQUIRE(result.size() == 8);
}