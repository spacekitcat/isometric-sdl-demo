#include <catch2/catch.hpp>
#include <iostream>

#include "../../util/pair-operators.hpp"

TEST_CASE(
    "Multiplies a pair by a quantity correctly (multiplicand == quantity)",
    "[Util::PairOperators::multiplyPairBy]") {
  auto multiplicand = std::make_pair(5, 5);
  auto quantity = 5;

  auto result = PairOperators::multiplyPairBy(multiplicand, quantity);
  REQUIRE(result.first == 25);
  REQUIRE(result.second == 25);
}

TEST_CASE("Multiplies a pair by a quantity correctly (multiplicand is "
          "multiplicative identity)",
          "[Util::PairOperators::multiplyPairBy]") {
  auto multiplicand = std::make_pair(5, 5);
  auto quantity = 1;

  auto result = PairOperators::multiplyPairBy(multiplicand, quantity);
  REQUIRE(result.first == 5);
  REQUIRE(result.second == 5);
}

TEST_CASE("Multiplies a pair by a quantity correctly (small quantity, "
          "1/60th game step scenario)",
          "[Util::PairOperators::multiplyPairBy]") {
  auto multiplicand = std::make_pair(5, 5);
  auto quantity = 0.2;

  auto result = PairOperators::multiplyPairBy(multiplicand, quantity);
  REQUIRE(result.first == Approx(1).scale(0.1));
  REQUIRE(result.second == Approx(1).scale(0.1));
}