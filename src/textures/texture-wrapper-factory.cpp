#include "texture-wrapper-factory.hpp"

TextureWrapperFactory::TextureWrapperFactory(
    std::shared_ptr<SDLManager> sdlManager) : _sdlManager(sdlManager) {
}

TextureWrapperFactory::~TextureWrapperFactory() {}

std::shared_ptr<TextureWrapper> TextureWrapperFactory::createTexture(SDL_Surface *from_surface) {
    return std::make_shared<TextureWrapper>(SDL_CreateTextureFromSurface(_sdlManager->getRenderer(), from_surface));
}