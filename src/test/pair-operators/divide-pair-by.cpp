#include <catch2/catch.hpp>
#include <iostream>

#include "../../util/pair-operators.hpp"

TEST_CASE(
    "Divides a pair by a denominator correctly (numerator == denominator)",
    "[Util::PairOperators::dividePairBy]") {
  auto numerator = std::make_pair(5, 5);
  auto denominator = 5;

  auto result = PairOperators::dividePairBy(numerator, denominator);
  REQUIRE(result.first == 1);
  REQUIRE(result.second == 1);
}

TEST_CASE("Divides a pair by a denominator correctly (demoninator is "
          "multiplicative identity)",
          "[Util::PairOperators::dividePairBy]") {
  auto numerator = std::make_pair(5, 5);
  auto denominator = 1;

  auto result = PairOperators::dividePairBy(numerator, denominator);
  REQUIRE(result.first == 5);
  REQUIRE(result.second == 5);
}

TEST_CASE("Divides a pair by a denominator correctly (large denominator, "
          "1/60th game step scenario)",
          "[Util::PairOperators::dividePairBy]") {
  auto numerator = std::make_pair(5, 5);
  auto denominator = 60;

  auto result = PairOperators::dividePairBy(numerator, denominator);
  REQUIRE(result.first == Approx(0.08333f).scale(0.2));
  REQUIRE(result.second == Approx(0.08333f).scale(0.2));
}
