#include "debug-overlay.hpp"

DebugOverlay::DebugOverlay(std::shared_ptr<SDLManager> sdlManager,
                           std::shared_ptr<Camera> camera,
                           TextRenderer &textRenderer,
                           GameSaveState &gameSaveState,
                           std::shared_ptr<Configuration> configuration)
    : _textRenderer(textRenderer), _gameSaveState(gameSaveState),
      _configuration(configuration), _sdlManager(sdlManager), _camera(camera) {
  assert(_sdlManager != nullptr);
  assert(_camera != nullptr);
}

void DebugOverlay::render(long int ticks) {
  if (_configuration->getIsDebugMode()) {
    SDL_SetRenderDrawColor(_sdlManager->getRenderer(), 255, 255, 255, 255);
    _textRenderer.renderText(str(boost::format("cam: %1$+5d %2$+5d") %
                                 round(_camera->getPosition().first) %
                                 round(_camera->getPosition().second)),
                             std::make_pair(16, 0));
    _textRenderer.renderText(
        str(boost::format("seed: %1$+5d") % _gameSaveState.getGameSeed()),
        std::make_pair(16, 16));

    _textRenderer.renderText(
        str(boost::format("sector dimensions: %1$+5d %2$+5d") %
            round(_configuration->getSectorDimensions().first) %
            round(_configuration->getSectorDimensions().second)),
        std::make_pair(320, 0));

    _textRenderer.renderText(
        str(boost::format("       tile dimensions: %1$+5d %2$+5d") %
            round(_configuration->getTileDimensions().first) %
            round(_configuration->getTileDimensions().second)),
        std::make_pair(320, 16));

    _textRenderer.renderText(str(boost::format("Rover's Revenge")),
                             std::make_pair(850, 0));

    _textRenderer.renderText(
        str(boost::format("framerate: %1$5d") % (1000 / ticks)),
        std::make_pair(850, 16));
  }
}