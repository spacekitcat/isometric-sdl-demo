#ifndef TEXTUREWRAPPER_H
#define TEXTUREWRAPPER_H

#include <SDL.h>
#include <cassert>

class TextureWrapper  
{
	private:
		SDL_Texture *_texture;

	public:

		TextureWrapper(SDL_Texture *texture);
		~TextureWrapper();

		SDL_Texture* getSdlTexture();

};
#endif