#include <catch2/catch.hpp>
#include <iostream>

#include "../../map/sector-spatial-utils.hpp"

TEST_CASE("Correctly converts 0,0 (string) to integer pair",
          "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair("0,0");
  REQUIRE(result.first == 0);
  REQUIRE(result.second == 0);
}

TEST_CASE("Correctly converts 0,-1 (string) to integer pair",
          "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair("0,-1");
  REQUIRE(result.first == 0);
  REQUIRE(result.second == -1);
}