//

#include "coordinate-mapper.hpp"

std::pair<float, float>
CoordinateMapper::worldToScreen(std::pair<float, float> worldPosition, std::pair<int, int> screenDimensions,
                                std::pair<float, float> playerSpriteDimensions) {
  return std::make_pair<float, float>(
          -worldPosition.first + (screenDimensions.first / 2) -
          (playerSpriteDimensions.first / 2),
          worldPosition.second + (screenDimensions.second / 2) -
          (playerSpriteDimensions.second / 2));
}
