#include "sdl-manager.hpp"

SDLManager::SDLManager() {
    _screenDimensions = std::make_pair<int, int>(1024, 768);
    _window = SDL_CreateWindow(
      "SDL2Application4 (isometric demo)", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, _screenDimensions.first, _screenDimensions.second,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

std::pair<int, int> SDLManager::getWindowDimensions() {
  return _screenDimensions;
}

SDL_Window *SDLManager::getWindow() {
  return _window;
}

SDL_Renderer *SDLManager::getRenderer() {
  return _renderer;
}