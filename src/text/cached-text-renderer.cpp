#include "cached-text-renderer.hpp"

CachedTextRenderer::CachedTextRenderer(
    TextRenderer &textRenderer, std::shared_ptr<SDLManager> sdlManager,
    TextureWrapperFactory &textureWrapperFactory)
    : _textRenderer(textRenderer), _sdlManager(sdlManager),
      _textureWrapperFactory(textureWrapperFactory) {
  assert(_sdlManager != nullptr);

  _font = TTF_OpenFont("./assets/fonts/Lato-Bold.ttf", 16);

  if (!_font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
  }

  assert(_font != nullptr);
}

CachedTextRenderer::~CachedTextRenderer() {}

std::shared_ptr<TextureWrapper>
CachedTextRenderer::renderText(std::string text,
                               std::pair<float, float> position) {

  if (_textureCache.find(text) != _textureCache.end()) {
    int w, h;
    SDL_QueryTexture(_textureCache[text]->getSdlTexture(), NULL, NULL, &w, &h);
    SDL_Rect dest = {.x = position.first,
                     .y = position.second,
                     .w = w,
                     .h = h};
    SDL_RenderCopy(_sdlManager->getRenderer(),
                   _textureCache[text]->getSdlTexture(), NULL, &dest);
  } else {
    std::cout << "cache miss" << std::endl;
    // Black outline (background)
    TTF_SetFontOutline(_font, 1);
    SDL_Color textBgColor = {0, 0, 0};
    SDL_Surface *text_surface_bg =
        TTF_RenderText_Blended(_font, text.c_str(), textBgColor);

    // White fill (foreground)
    TTF_SetFontOutline(_font, 0);
    SDL_Color textFgColor = {255, 255, 255};
    SDL_Surface *text_surface_fg =
        TTF_RenderText_Blended(_font, text.c_str(), textFgColor);

    // Offset to center
    SDL_Rect offset = {.x = 1, .y = 1};
    SDL_BlitSurface(text_surface_fg, NULL, text_surface_bg, &offset);

    _textureCache[text] = _textureWrapperFactory.createTexture(text_surface_bg);
    SDL_Rect dest = {.x = position.first,
                     .y = position.second,
                     .w = text_surface_bg->w,
                     .h = text_surface_bg->h};
    SDL_RenderCopy(_sdlManager->getRenderer(),
                   _textureCache[text]->getSdlTexture(), NULL, &dest);
  }

  return _textureCache[text];
}