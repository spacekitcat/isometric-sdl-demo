#include "debug-overlay.hpp"

DebugOverlay::DebugOverlay(std::shared_ptr<SDLManager> sdlManager,
                           std::shared_ptr<Camera> camera) {
  _sdlManager = sdlManager;
  _camera = camera;

  assert(_sdlManager != nullptr);
  assert(_camera != nullptr);

  _font = TTF_OpenFont("./assets/fonts/Lato-Bold.ttf", 18);

  if (!_font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
  }

  assert(_font != nullptr);
}

void DebugOverlay::render() {
  SDL_SetRenderDrawColor(_sdlManager->getRenderer(), 255, 255, 255, 255);
  renderText(
      str(boost::format("%1$+5d %2$+5d") % round(_camera->getPosition().first) %
          round(_camera->getPosition().second)));
}

void DebugOverlay::renderText(std::string text) {
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

  // Text conversion
  SDL_Texture *tex =
      SDL_CreateTextureFromSurface(_sdlManager->getRenderer(), text_surface_bg);

  SDL_Rect dest = {
      .x = 100, .y = 25, .w = text_surface_bg->w, .h = text_surface_bg->h};
  SDL_RenderCopy(_sdlManager->getRenderer(), tex, NULL, &dest);

  SDL_DestroyTexture(tex);

  SDL_FreeSurface(text_surface_bg);
  SDL_FreeSurface(text_surface_fg);
}