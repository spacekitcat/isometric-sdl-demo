#include "sdl-manager.hpp"

SDLManager::SDLManager(std::shared_ptr<Configuration> configuration)
    : _configuration(configuration) {
  std::cout << "Constructing SDLManager" << std::endl;
  _screenDimensions =
      std::make_pair<int, int>(configuration->getWindowDimensions().first,
                               configuration->getWindowDimensions().second);
  _window = SDL_CreateWindow("Rover's Revenge", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, _screenDimensions.first,
                             _screenDimensions.second,
                             SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  _renderer = SDL_CreateRenderer(
      _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDLManager::~SDLManager() {
  std::cout << "Destroying SDLManager" << std::endl;
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

SDL_Window *SDLManager::getWindow() { return _window; }

SDL_Renderer *SDLManager::getRenderer() { return _renderer; }

void SDLManager::renderClear() { SDL_RenderClear(this->getRenderer()); }
