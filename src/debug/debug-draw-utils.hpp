#pragma once

#include <SDL.h>
#include <iostream>

#include "../render/sdl-manager.hpp"

class DebugDrawUtils {
public:
  static void drawBox(SDLManager *sdlManager, std::pair<float, float> origin,
                      std::pair<float, float> dimensions, bool center);
};
