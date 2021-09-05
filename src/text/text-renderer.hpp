#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <boost/format.hpp>

#include "../../lib/SDL_FontCache/SDL_FontCache.h"
#include "../render/sdl-manager.hpp"

class TextRenderer {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  FC_Font *_backgroundFont;
  FC_Font *_foregroundFont;

public:
  TextRenderer(std::shared_ptr<SDLManager> sdlManager);
  ~TextRenderer();

  void renderText(std::string text, std::pair<float, float> position);
};
