#ifndef SDL2APPLICATION4_TEXT_RENDERER_HPP
#define SDL2APPLICATION4_TEXT_RENDERER_HPP

#include <SDL_ttf.h>
#include <SDL.h>
#include <boost/format.hpp>

#include "../render/sdl-manager.hpp"
#include "../textures/texture-wrapper.hpp"
#include "../textures/texture-wrapper-factory.hpp"

class TextRenderer {
    private:
        std::shared_ptr<SDLManager> _sdlManager;
        TextureWrapperFactory &_textureWrapperFactory;
        TTF_Font *_font;
    
    public:
        TextRenderer(std::shared_ptr<SDLManager> sdlManager, TextureWrapperFactory &textureWrapperFactory);
        ~TextRenderer();

        std::shared_ptr<TextureWrapper> renderText(std::string text, std::pair<float, float> position);
};

#endif //SDL2APPLICATION4_TEXT_RENDERER_HPP
