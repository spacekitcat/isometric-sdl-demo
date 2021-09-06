#pragma once

#include <iostream>

class PairOperators {
public:
  static std::pair<float, float> addPair(std::pair<float, float> first,
                                         std::pair<float, float> second);

  static std::pair<float, float> dividePairBy(std::pair<float, float> numerator,
                                              long int denominator);

  static std::pair<float, float>
  multiplyPairBy(std::pair<float, float> multiplicand, float quantity);
};