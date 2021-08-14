#ifndef SDL2APPLICATION4_SDL_MANAGER_HPP
#define SDL2APPLICATION4_SDL_MANAGER_HPP

#include <iostream>
#include <SDL.h>

class SDLManager {
private:
    std::pair<int, int> _screenDimensions;

  SDL_Window *_window;
  SDL_Renderer *_renderer;


public:
  SDLManager();

  std::pair<int, int> getWindowDimensions();

  SDL_Window* getWindow();

  SDL_Renderer* getRenderer();
};


#endif //SDL2APPLICATION4_SDL_MANAGER_HPP
