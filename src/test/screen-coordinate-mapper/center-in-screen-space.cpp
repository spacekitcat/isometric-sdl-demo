#include <catch2/catch.hpp>
#include <iostream>

#include "../../config/configuration.hpp"
#include "../../map/camera.hpp"
#include "../../map/screen-coordinate-mapper.hpp"

TEST_CASE("Maps world 0,0 (1x) to screen index 50%,50% (1x)",
          "[Map::screen-coordinate-mapper::centerInScreenSpace]") {

  auto specifiedConfiguration = std::make_shared<Configuration>();
  auto specifiedCamera = std::make_shared<Camera>();

  specifiedConfiguration->setWindowDimensions(std::make_pair(600, 600));
  specifiedCamera->setZoom(1.0f);

  auto *sut =
      new ScreenCoordinateMapper(specifiedConfiguration, specifiedCamera);

  auto result = sut->centerInScreenSpace(std::make_pair(0, 0));
  REQUIRE(result.first == 300);
  REQUIRE(result.second == 300);
}

TEST_CASE("Maps world 0,0 (.5x) to screen index 50%,50% (.5x)",
          "[Map::screen-coordinate-mapper::centerInScreenSpace]") {

  auto specifiedConfiguration = std::make_shared<Configuration>();
  auto specifiedCamera = std::make_shared<Camera>();

  specifiedConfiguration->setWindowDimensions(std::make_pair(600, 600));
  specifiedCamera->setZoom(.5f);

  auto *sut =
      new ScreenCoordinateMapper(specifiedConfiguration, specifiedCamera);

  auto result = sut->centerInScreenSpace(std::make_pair(0, 0));
  REQUIRE(result.first == 600);
  REQUIRE(result.second == 600);
}