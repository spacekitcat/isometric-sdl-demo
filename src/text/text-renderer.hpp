#ifndef SDL2APPLICATION4_TEXT_RENDERER_HPP
#define SDL2APPLICATION4_TEXT_RENDERER_HPP

#include <SDL_ttf.h>
#include <SDL.h>
#include <boost/format.hpp>

#include "../render/sdl-manager.hpp"

class TextRenderer {
    private:
        std::shared_ptr<SDLManager> _sdlManager;
        TTF_Font *_font;
    
    public:
        TextRenderer(std::shared_ptr<SDLManager> sdlManager);
        ~TextRenderer();

        void renderText(std::string text, std::pair<float, float> position);
};

#endif //SDL2APPLICATION4_TEXT_RENDERER_HPP
