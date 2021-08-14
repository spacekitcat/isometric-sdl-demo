#ifndef SDL2APPLICATION4_DEBUG_DRAW_UTILS_HPP
#define SDL2APPLICATION4_DEBUG_DRAW_UTILS_HPP

#include <iostream>
#include <SDL.h>

class DebugDrawUtils {
public:
  static void drawBox(SDL_Renderer *renderer, std::pair<float, float> origin, std::pair<float, float> dimensions, bool center);
};


#endif //SDL2APPLICATION4_DEBUG_DRAW_UTILS_HPP
