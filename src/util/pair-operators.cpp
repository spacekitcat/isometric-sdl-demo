#include "pair-operators.hpp"

#include <utility>

std::pair<float, float> PairOperators::addPair(std::pair<float, float> first,
                                               std::pair<float, float> second) {
  return std::make_pair(first.first + second.first,
                        first.second + second.second);
}
