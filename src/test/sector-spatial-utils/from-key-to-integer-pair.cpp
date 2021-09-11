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

TEST_CASE("Correctly converts 0,1 (string) to integer pair",
          "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair("0,1");
  REQUIRE(result.first == 0);
  REQUIRE(result.second == 1);
}

TEST_CASE("Correctly converts -1,0 (string) to integer pair",
          "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair("-1,0");
  REQUIRE(result.first == -1);
  REQUIRE(result.second == 0);
}

TEST_CASE("Correctly converts 1,0 (string) to integer pair",
          "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair("1,0");
  REQUIRE(result.first == 1);
  REQUIRE(result.second == 0);
}

TEST_CASE("Correctly converts 100,100 (string) to integer pair",
          "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair("100,100");
  REQUIRE(result.first == 100);
  REQUIRE(result.second == 100);
}

TEST_CASE("Correctly converts -100,-100 (string) to integer pair",
          "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair("-100,-100");
  REQUIRE(result.first == -100);
  REQUIRE(result.second == -100);
}

TEST_CASE(
    "Correctly converts integer pair with extra space after the delimiter",
    "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair("100, 100");
  REQUIRE(result.first == 100);
  REQUIRE(result.second == 100);
}

TEST_CASE(
    "Correctly converts integer pair with extra space before the delimiter",
    "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair("100 ,100");
  REQUIRE(result.first == 100);
  REQUIRE(result.second == 100);
}

TEST_CASE("Correctly converts integer pair with extra space prefix",
          "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair(" 100,100");
  REQUIRE(result.first == 100);
  REQUIRE(result.second == 100);
}

TEST_CASE("Correctly converts integer pair with extra space suffix",
          "[Map::SectorSpatialUtils::fromKeyToIntegerPair]") {
  auto sut = new SectorSpatialUtils();

  auto result = sut->fromKeyToIntegerPair("100,100 ");
  REQUIRE(result.first == 100);
  REQUIRE(result.second == 100);
}
