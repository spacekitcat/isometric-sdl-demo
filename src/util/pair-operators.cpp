#include "pair-operators.hpp"

#include <utility>

std::pair<float, float> PairOperators::addPair(std::pair<float, float> first,
                                               std::pair<float, float> second) {
  return std::make_pair(first.first + second.first,
                        first.second + second.second);
}

std::pair<float, float>
PairOperators::dividePairBy(std::pair<float, float> numerator,
                            long int denominator) {
  return std::make_pair(numerator.first / denominator,
                        numerator.second / denominator);
}

std::pair<float, float>
PairOperators::multiplyPairBy(std::pair<float, float> multiplicand,
                              float quantity) {
  return std::make_pair(multiplicand.first * quantity,
                        multiplicand.second * quantity);
}