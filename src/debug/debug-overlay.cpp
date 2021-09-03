#include "debug-overlay.hpp"

DebugOverlay::DebugOverlay(std::shared_ptr<SDLManager> sdlManager,
                           std::shared_ptr<Camera> camera,
                           CachedTextRenderer &textRenderer,
                           GameSaveState &gameSaveState)
    : _textRenderer(textRenderer), _gameSaveState(gameSaveState) {
  _sdlManager = sdlManager;
  _camera = camera;

  assert(_sdlManager != nullptr);
  assert(_camera != nullptr);
}

void DebugOverlay::render() {
  SDL_SetRenderDrawColor(_sdlManager->getRenderer(), 255, 255, 255, 255);
  _textRenderer.renderText(str(boost::format("cam: %1$+5d %2$+5d") %
                               round(_camera->getPosition().first) %
                               round(_camera->getPosition().second)),
                           std::make_pair(16, 8));

  _textRenderer.renderText(
      str(boost::format("seed: %1$+5d") % _gameSaveState.getGameSeed()),
      std::make_pair(160, 8));

  _textRenderer.renderText(
      str(boost::format("sector dimensions: %1$+5d %2$+5d") %
          round(_gameSaveState.getSectorDimensions().first) %
          round(_gameSaveState.getSectorDimensions().second)),
      std::make_pair(320, 8));

  _textRenderer.renderText(
      str(boost::format("       tile dimensions: %1$+5d %2$+5d") %
          round(_gameSaveState.getTileDimensions().first) %
          round(_gameSaveState.getTileDimensions().second)),
      std::make_pair(320, 24));

  _textRenderer.renderText(
      str(boost::format("Rover's Revenge")),
      std::make_pair(890, 8));
}