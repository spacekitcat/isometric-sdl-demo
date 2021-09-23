#include <catch2/catch.hpp>
#include <iostream>

#include "../../config/configuration.hpp"
#include "../../map/world-to-map-sector-index.hpp"

TEST_CASE("Maps world 0,0 to sector index 0,0",
          "[Map::WorldToMapSectorIndex::getMapIndex]") {

  Configuration providedConfiguration;
  providedConfiguration.setSectorDimensions(std::make_pair(500, 500));
  providedConfiguration.setTileDimensions(std::make_pair(50, 50));

  auto sut = new WorldToMapSectorIndex(providedConfiguration);
  auto result = sut->getMapIndex(std::make_pair(0, 0));

  REQUIRE(result.first == 0);
  REQUIRE(result.second == 0);
}

TEST_CASE("Maps world 1,1 to sector index 0,0",
          "[Map::WorldToMapSectorIndex::getMapIndex]") {

  Configuration providedConfiguration;
  providedConfiguration.setSectorDimensions(std::make_pair(500, 500));
  providedConfiguration.setTileDimensions(std::make_pair(50, 50));

  auto sut = new WorldToMapSectorIndex(providedConfiguration);
  auto result = sut->getMapIndex(std::make_pair(1, 1));

  REQUIRE(result.first == 0);
  REQUIRE(result.second == 0);
}

TEST_CASE("Maps world -1,-1 to sector index 0,0",
          "[Map::WorldToMapSectorIndex::getMapIndex]") {

  Configuration providedConfiguration;
  providedConfiguration.setSectorDimensions(std::make_pair(500, 500));
  providedConfiguration.setTileDimensions(std::make_pair(50, 50));

  auto sut = new WorldToMapSectorIndex(providedConfiguration);
  auto result = sut->getMapIndex(std::make_pair(1, 1));

  REQUIRE(result.first == 0);
  REQUIRE(result.second == 0);
}

TEST_CASE("Maps world 500,500 to sector index 1,1",
          "[Map::WorldToMapSectorIndex::getMapIndex]") {

  Configuration providedConfiguration;
  providedConfiguration.setSectorDimensions(std::make_pair(500, 500));
  providedConfiguration.setTileDimensions(std::make_pair(50, 50));

  auto sut = new WorldToMapSectorIndex(providedConfiguration);
  auto result = sut->getMapIndex(std::make_pair(500, 500));

  REQUIRE(result.first == 1);
  REQUIRE(result.second == 1);
}

TEST_CASE("Maps world -500,-500 to sector index -1,-1",
          "[Map::WorldToMapSectorIndex::getMapIndex]") {

  Configuration providedConfiguration;
  providedConfiguration.setSectorDimensions(std::make_pair(500, 500));
  providedConfiguration.setTileDimensions(std::make_pair(50, 50));

  auto sut = new WorldToMapSectorIndex(providedConfiguration);
  auto result = sut->getMapIndex(std::make_pair(-500, -500));

  REQUIRE(result.first == -2);
  REQUIRE(result.second == -2);
}

TEST_CASE("Maps world 500,-500 to sector index 1,-1",
          "[Map::WorldToMapSectorIndex::getMapIndex]") {

  Configuration providedConfiguration;
  providedConfiguration.setSectorDimensions(std::make_pair(500, 500));
  providedConfiguration.setTileDimensions(std::make_pair(50, 50));

  auto sut = new WorldToMapSectorIndex(providedConfiguration);
  auto result = sut->getMapIndex(std::make_pair(500, -500));

  REQUIRE(result.first == 1);
  REQUIRE(result.second == -2);
}

TEST_CASE("Maps world -500,500 to sector index -1,1",
          "[Map::WorldToMapSectorIndex::getMapIndex]") {

  Configuration providedConfiguration;
  providedConfiguration.setSectorDimensions(std::make_pair(500, 500));
  providedConfiguration.setTileDimensions(std::make_pair(50, 50));

  auto sut = new WorldToMapSectorIndex(providedConfiguration);
  auto result = sut->getMapIndex(std::make_pair(-500, 500));

  REQUIRE(result.first == -2);
  REQUIRE(result.second == 1);
}