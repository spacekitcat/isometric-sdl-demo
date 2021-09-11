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

TEST_CASE("Correctly converts 0,1 (int) to string key",
          "[Map::SectorSpatialUtils::fromIntegerPairToKey]") {
  auto specifiedPair = std::make_pair(0, 1);

  auto sut = new SectorSpatialUtils();

  auto result = sut->fromIntegerPairToKey(specifiedPair);
  REQUIRE(result.compare("0,1") == 0);
}

TEST_CASE("Correctly converts 0,-1 (int) to string key",
          "[Map::SectorSpatialUtils::fromIntegerPairToKey]") {
  auto specifiedPair = std::make_pair(0, -1);

  auto sut = new SectorSpatialUtils();

  auto result = sut->fromIntegerPairToKey(specifiedPair);
  REQUIRE(result.compare("0,-1") == 0);
}

TEST_CASE("Correctly converts 1,0 (int) to string key",
          "[Map::SectorSpatialUtils::fromIntegerPairToKey]") {
  auto specifiedPair = std::make_pair(1, 0);

  auto sut = new SectorSpatialUtils();

  auto result = sut->fromIntegerPairToKey(specifiedPair);
  REQUIRE(result.compare("1,0") == 0);
}

TEST_CASE("Correctly converts -1,0 (int) to string key",
          "[Map::SectorSpatialUtils::fromIntegerPairToKey]") {
  auto specifiedPair = std::make_pair(-1, 0);

  auto sut = new SectorSpatialUtils();

  auto result = sut->fromIntegerPairToKey(specifiedPair);
  REQUIRE(result.compare("-1,0") == 0);
}

TEST_CASE("Correctly converts 100,100 (int) to string key",
          "[Map::SectorSpatialUtils::fromIntegerPairToKey]") {
  auto specifiedPair = std::make_pair(100, 100);

  auto sut = new SectorSpatialUtils();

  auto result = sut->fromIntegerPairToKey(specifiedPair);
  REQUIRE(result.compare("100,100") == 0);
}

TEST_CASE("Correctly converts 100,-100 (int) to string key",
          "[Map::SectorSpatialUtils::fromIntegerPairToKey]") {
  auto specifiedPair = std::make_pair(100, -100);

  auto sut = new SectorSpatialUtils();

  auto result = sut->fromIntegerPairToKey(specifiedPair);
  REQUIRE(result.compare("100,-100") == 0);
}

TEST_CASE("Correctly converts -100,100 (int) to string key",
          "[Map::SectorSpatialUtils::fromIntegerPairToKey]") {
  auto specifiedPair = std::make_pair(-100, 100);

  auto sut = new SectorSpatialUtils();

  auto result = sut->fromIntegerPairToKey(specifiedPair);
  REQUIRE(result.compare("-100,100") == 0);
}