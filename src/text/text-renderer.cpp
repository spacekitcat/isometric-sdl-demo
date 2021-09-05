#include "text-renderer.hpp"

TextRenderer::TextRenderer(std::shared_ptr<SDLManager> sdlManager) {
  _sdlManager = sdlManager;

  assert(_sdlManager != nullptr);
  SDL_Color textFgColor = {255, 255, 255};
  SDL_Color textBgColor = {0, 0, 0};
  FC_Style style = {.fontSize=16, .outline=1,.color=textFgColor,.outline_color=textBgColor};
  _backgroundFont = FC_CreateFont();
  FC_LoadFontFromStyle(_backgroundFont, _sdlManager->getRenderer(), "./assets/fonts/Lato-Bold.ttf", &style);
}

TextRenderer::~TextRenderer() {
  //delete _backgroundFont;
}

void TextRenderer::renderText(std::string text, std::pair<float, float> position) {
  FC_Draw(_backgroundFont, _sdlManager->getRenderer(), position.first, position.second, text.c_str());
}