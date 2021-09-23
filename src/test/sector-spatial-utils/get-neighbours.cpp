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

TEST_CASE("Correctly gets the neighbours for 0,0 (radius 1)",
          "[Map::SectorSpatialUtils::getNeighbours]") {

  std::pair<int, int> specifiedPair = std::make_pair(0, 0);
  auto sut = new SectorSpatialUtils();

  auto result = sut->getNeighbours(specifiedPair, 1);

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

TEST_CASE("Correctly gets the neighbours for 0,0 (radius 2)",
          "[Map::SectorSpatialUtils::getNeighbours]") {

  std::pair<int, int> specifiedPair = std::make_pair(0, 0);
  auto sut = new SectorSpatialUtils();

  auto result = sut->getNeighbours(specifiedPair, 2);

  REQUIRE(result.size() == 24);
  REQUIRE(listContains(result, std::make_pair<int, int>(-2, -2)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-2, -1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-2, 0)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-2, 1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-2, 2)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-1, -2)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-1, -1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-1, 0)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-1, 1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-1, 2)));
  REQUIRE(listContains(result, std::make_pair<int, int>(0, -2)));
  REQUIRE(listContains(result, std::make_pair<int, int>(0, -1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(0, 1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(0, 2)));
  REQUIRE(listContains(result, std::make_pair<int, int>(1, -2)));
  REQUIRE(listContains(result, std::make_pair<int, int>(1, -1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(1, 0)));
  REQUIRE(listContains(result, std::make_pair<int, int>(1, 1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(1, 2)));
  REQUIRE(listContains(result, std::make_pair<int, int>(2, -2)));
  REQUIRE(listContains(result, std::make_pair<int, int>(2, -1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(2, 0)));
  REQUIRE(listContains(result, std::make_pair<int, int>(2, 1)));
  REQUIRE(listContains(result, std::make_pair<int, int>(2, 2)));
}

TEST_CASE("Correctly gets the neighbours for 100,100",
          "[Map::SectorSpatialUtils::getNeighbours]") {

  std::pair<int, int> specifiedPair = std::make_pair(100, 100);
  auto sut = new SectorSpatialUtils();

  auto result = sut->getNeighbours(specifiedPair);

  REQUIRE(result.size() == 8);
  REQUIRE(listContains(result, std::make_pair<int, int>(99, 100)));
  REQUIRE(listContains(result, std::make_pair<int, int>(99, 101)));
  REQUIRE(listContains(result, std::make_pair<int, int>(100, 101)));
  REQUIRE(listContains(result, std::make_pair<int, int>(101, 101)));
  REQUIRE(listContains(result, std::make_pair<int, int>(101, 100)));
  REQUIRE(listContains(result, std::make_pair<int, int>(101, 99)));
  REQUIRE(listContains(result, std::make_pair<int, int>(100, 99)));
  REQUIRE(listContains(result, std::make_pair<int, int>(99, 99)));
}

TEST_CASE("Correctly gets the neighbours for -100,-100",
          "[Map::SectorSpatialUtils::getNeighbours]") {

  std::pair<int, int> specifiedPair = std::make_pair(-100, -100);
  auto sut = new SectorSpatialUtils();

  auto result = sut->getNeighbours(specifiedPair);

  REQUIRE(result.size() == 8);
  REQUIRE(listContains(result, std::make_pair<int, int>(-99, -100)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-99, -101)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-100, -101)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-101, -101)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-101, -100)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-101, -99)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-100, -99)));
  REQUIRE(listContains(result, std::make_pair<int, int>(-99, -99)));
}