#include <catch2/catch.hpp>
#include <iostream>

#include "../../util/pair-operators.hpp"

TEST_CASE("Adds two pairs positive number pairs correctly",
          "[Util::PairOperators::addPair]") {
  auto firstSpecifiedPair = std::make_pair(1, 1);
  auto secondSpecifiedPair = std::make_pair(1, 1);

  auto result = PairOperators::addPair(firstSpecifiedPair, secondSpecifiedPair);
  REQUIRE(result.first == 2);
  REQUIRE(result.second == 2);
}

TEST_CASE("Adds two pairs negative number pairs correctly",
          "[Util::PairOperators::addPair]") {
  auto firstSpecifiedPair = std::make_pair(-1, -1);
  auto secondSpecifiedPair = std::make_pair(-1, -1);

  auto result = PairOperators::addPair(firstSpecifiedPair, secondSpecifiedPair);
  REQUIRE(result.first == -2);
  REQUIRE(result.second == -2);
}

TEST_CASE("Adds two pairs mixed number pairs correctly",
          "[Util::PairOperators::addPair]") {
  auto firstSpecifiedPair = std::make_pair(1, -1);
  auto secondSpecifiedPair = std::make_pair(-1, 1);

  auto result = PairOperators::addPair(firstSpecifiedPair, secondSpecifiedPair);
  REQUIRE(result.first == 0);
  REQUIRE(result.second == 0);
}