#include "text-renderer.hpp"

TextRenderer::TextRenderer(std::shared_ptr<SDLManager> sdlManager) {
  _sdlManager = sdlManager;

  assert(_sdlManager != nullptr);

  _backgroundFont = FC_CreateFont();
  FC_LoadFont(_backgroundFont, _sdlManager->getRenderer(), "./assets/fonts/Lato-Bold.ttf", 16, FC_MakeColor(0,0,0,255), TTF_STYLE_OUTLINE);
  _foregroundFont = FC_CreateFont();
  FC_LoadFont(_foregroundFont, _sdlManager->getRenderer(), "./assets/fonts/Lato-Bold.ttf", 16, FC_MakeColor(255,255,255,255), TTF_STYLE_NORMAL);
}

TextRenderer::~TextRenderer() {
  //delete _backgroundFont;
}

void TextRenderer::renderText(std::string text, std::pair<float, float> position) {
  FC_Draw(_backgroundFont, _sdlManager->getRenderer(), position.first, position.second, text.c_str());
  FC_Draw(_foregroundFont, _sdlManager->getRenderer(), position.first, position.second, text.c_str());
  // // Black outline (background)
  // TTF_SetFontOutline(_backgroundFont, 1);
  // SDL_Color textBgColor = {0, 0, 0};
  // SDL_Surface *text_surface_bg =
  //     TTF_RenderText_Blended(_backgroundFont, text.c_str(), textBgColor);

  // // White fill (foreground)
  // TTF_SetFontOutline(_backgroundFont, 0);
  // SDL_Color textFgColor = {255, 255, 255};
  // SDL_Surface *text_surface_fg =
  //     TTF_RenderText_Blended(_backgroundFont, text.c_str(), textFgColor);

  // // Offset to center
  // SDL_Rect offset = {.x = 1, .y = 1};
  // SDL_BlitSurface(text_surface_fg, NULL, text_surface_bg, &offset);

  // // Text conversion
  // SDL_Texture *tex =
  //     SDL_CreateTextureFromSurface(_sdlManager->getRenderer(), text_surface_bg);

  // SDL_Rect dest = {
  //     .x = position.first, .y = position.second, .w = text_surface_bg->w, .h = text_surface_bg->h};
  // SDL_RenderCopy(_sdlManager->getRenderer(), tex, NULL, &dest);

  // SDL_DestroyTexture(tex);

  // SDL_FreeSurface(text_surface_bg);
  // SDL_FreeSurface(text_surface_fg);
}