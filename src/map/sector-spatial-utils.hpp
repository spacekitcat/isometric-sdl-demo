#pragma once

#include <boost/format.hpp>
#include <iostream>

class SectorSpatialUtils {
private:
public:
  SectorSpatialUtils();
  ~SectorSpatialUtils();

  std::string fromIntegerPairToKey(std::pair<int, int> integerPair);
};