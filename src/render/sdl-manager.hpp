#pragma once

#include "../config/configuration.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <exception>
#include <iostream>

class SDLManager {
private:
  std::shared_ptr<Configuration> _configuration;
  std::pair<int, int> _screenDimensions;
  SDL_Window *_window;
  SDL_Renderer *_renderer;

public:
  SDLManager(std::shared_ptr<Configuration> configuration);
  ~SDLManager();

  SDL_Window *getWindow();

  SDL_Renderer *getRenderer();

  void renderClear();
};
