#include "debug-draw-utils.hpp"

void DebugDrawUtils::drawBox(SDL_Renderer *renderer, std::pair<float, float> worldOrigin, std::pair<float, float> dimensions, bool center) {
  SDL_Rect rectangleRect = {
          .x = worldOrigin.first,
          .y = worldOrigin.second,
          .w = dimensions.first,
          .h = dimensions.second,
          };
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderDrawRect(renderer, &rectangleRect);
}
