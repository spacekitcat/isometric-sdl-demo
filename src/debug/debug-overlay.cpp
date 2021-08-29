#include "debug-overlay.hpp"

DebugOverlay::DebugOverlay(std::shared_ptr<SDLManager> sdlManager,
                           std::shared_ptr<Camera> camera, TextRenderer &textRenderer): _textRenderer(textRenderer) {
  _sdlManager = sdlManager;
  _camera = camera;

  assert(_sdlManager != nullptr);
  assert(_camera != nullptr);
}

void DebugOverlay::render() {
  SDL_SetRenderDrawColor(_sdlManager->getRenderer(), 255, 255, 255, 255);
  renderText(
      str(boost::format("%1$+5d %2$+5d") % round(_camera->getPosition().first) %
          round(_camera->getPosition().second)));
}

void DebugOverlay::renderText(std::string text) {
  _textRenderer.renderText(text);
}