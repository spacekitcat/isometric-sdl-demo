#include <catch2/catch.hpp>
#include <iostream>

#include "../../config/configuration.hpp"
#include "../../map/camera.hpp"
#include "../../map/screen-coordinate-mapper.hpp"

TEST_CASE("Maps world 0,0 to screen index 50%,50%",
          "[Map::screen-coordinate-mapper::centerInScreenSpace]") {

  auto specifiedConfiguration = std::make_shared<Configuration>();
  auto specifiedCamera = std::make_shared<Camera>();

  auto sut =
      new ScreenCoordinateMapper(specifiedConfiguration, specifiedCamera);

  sut.centerInScreenSpace(std::make_pair(0, 0));
}