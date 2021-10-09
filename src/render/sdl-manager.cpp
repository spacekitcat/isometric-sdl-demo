#include "sdl-manager.hpp"

SDLManager::SDLManager(std::shared_ptr<Configuration> configuration)
    : _configuration(configuration) {
  std::cout << "Constructing SDLManager" << std::endl;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    throw new std::runtime_error("Unable to initialize SDL");
  }

  _screenDimensions =
      std::make_pair<int, int>(configuration->getWindowDimensions().first,
                               configuration->getWindowDimensions().second);
  _window = SDL_CreateWindow("Rover's Revenge", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, _screenDimensions.first,
                             _screenDimensions.second,
                             SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  _renderer = SDL_CreateRenderer(
      _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  int audioFlags = MIX_INIT_MP3 | MIX_INIT_MOD;
  int audioInitState = Mix_Init(audioFlags);
  if (audioInitState & !audioFlags) {
    printf("Mix_Init: Failed to init required ogg and mod support!\n");
    printf("Mix_Init: %s\n", Mix_GetError());
    throw new std::runtime_error("Unable to initialize SDL Audio");
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
    throw new std::runtime_error("Unable to open SDL Audio device");
  }
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
