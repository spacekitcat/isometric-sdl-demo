#include <catch2/catch.hpp>
#include <iostream>

#include "../../map/sector-spatial-utils.hpp"

TEST_CASE("Correctly converts 0,0 (int) to string key",
          "[Map::SectorSpatialUtils::fromIntegerPairToKey]") {
  auto specifiedPair = std::make_pair(0, 0);

  auto sut = new SectorSpatialUtils();

  auto result = sut->fromIntegerPairToKey(specifiedPair);
  REQUIRE(result.compare("0,0") == 0);
}