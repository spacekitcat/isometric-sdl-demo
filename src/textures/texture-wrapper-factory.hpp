#ifndef TEXTUREWRAPPERFACTORY_H
#define TEXTUREWRAPPERFACTORY_H

#include <SDL.h>
#include <iostream>

#include "../render/sdl-manager.hpp"
#include "../textures/texture-wrapper.hpp"

class TextureWrapperFactory {
private:
  std::shared_ptr<SDLManager> _sdlManager;

public:
  TextureWrapperFactory(std::shared_ptr<SDLManager> sdlManager);
  ~TextureWrapperFactory();

  std::shared_ptr<TextureWrapper> createTexture(SDL_Surface *from);
};
#endif