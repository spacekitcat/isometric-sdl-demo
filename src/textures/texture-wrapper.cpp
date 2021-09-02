#include "texture-wrapper.hpp"  
	
TextureWrapper::TextureWrapper(SDL_Texture *texture)
{
    assert(texture != NULL);

	_texture = texture;
}
	
TextureWrapper::~TextureWrapper()
{
	SDL_DestroyTexture(_texture);
}

SDL_Texture* TextureWrapper::getSdlTexture() {
	return _texture;
}