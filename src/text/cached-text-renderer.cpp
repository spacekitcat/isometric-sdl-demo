#include "cached-text-renderer.hpp"

CachedTextRenderer::CachedTextRenderer(TextRenderer &textRenderer)
    : _textRenderer(textRenderer) {}

CachedTextRenderer::~CachedTextRenderer() {}

std::shared_ptr<TextureWrapper>
CachedTextRenderer::renderText(std::string text, std::pair<float, float> position) {
    return _textRenderer.renderText(text, position);
}