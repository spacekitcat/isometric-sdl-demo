#ifndef SDL2APPLICATION4_COORDINATE_MAPPER_HPP
#define SDL2APPLICATION4_COORDINATE_MAPPER_HPP

#include <iostream>

class CoordinateMapper {
public:
  static std::pair<float, float>
  worldToScreen(std::pair<float, float> worldPosition,
                std::pair<int, int> screenDimensions,
                std::pair<float, float> playerSpriteDimensions);

};

#endif // SDL2APPLICATION4_COORDINATE_MAPPER_HPP
