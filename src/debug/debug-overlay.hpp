#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <boost/format.hpp>

#include "../map/camera.hpp"
#include "../render/sdl-manager.hpp"
#include "../state/game-save-state.hpp"
#include "../text/text-renderer.hpp"

class DebugOverlay {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::shared_ptr<Camera> _camera;
  TextRenderer _textRenderer;
  GameSaveState _gameSaveState;

public:
  DebugOverlay(std::shared_ptr<SDLManager> sdlManager,
               std::shared_ptr<Camera> camera, TextRenderer &textRenderer,
               GameSaveState &gameSaveState);

  void render();
};
