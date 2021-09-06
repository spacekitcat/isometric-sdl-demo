#pragma once

#include <SDL.h>
#include <iostream>

class SDLManager {
private:
  std::pair<int, int> _screenDimensions;

  SDL_Window *_window;

  SDL_Renderer *_renderer;

public:
  SDLManager();
  ~SDLManager();

  std::pair<int, int> getWindowDimensions();

  SDL_Window *getWindow();

  SDL_Renderer *getRenderer();

  void renderClear();
};
