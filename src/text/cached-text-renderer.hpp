#ifndef CACHEDTEXTRENDERER_H
#define CACHEDTEXTRENDERER_H

#include <SDL.h>
#include <iostream>
#include <map>

#include "../text/text-renderer.hpp"
#include "../textures/texture-wrapper.hpp"

class CachedTextRenderer {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  TextRenderer &_textRenderer;
  std::map<std::string, std::shared_ptr<TextureWrapper>> _textureCache;
  TextureWrapperFactory &_textureWrapperFactory;
  TTF_Font *_font;

public:
  CachedTextRenderer(TextRenderer &textRenderer,
                     std::shared_ptr<SDLManager> sdlManager, TextureWrapperFactory &textureWrapperFactory);
  ~CachedTextRenderer();

  std::shared_ptr<TextureWrapper> renderText(std::string text,
                                             std::pair<float, float> position);
};
#endif