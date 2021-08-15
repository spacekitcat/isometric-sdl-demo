#ifndef SDL2APPLICATION4_DEBUG_DRAW_UTILS_HPP
#define SDL2APPLICATION4_DEBUG_DRAW_UTILS_HPP

#include <iostream>
#include <SDL.h>

#include "../render/sdl-manager.hpp"

class DebugDrawUtils {
public:
  static void drawBox(SDLManager *sdlManager, std::pair<float, float> origin, std::pair<float, float> dimensions, bool center);
};


#endif //SDL2APPLICATION4_DEBUG_DRAW_UTILS_HPP
