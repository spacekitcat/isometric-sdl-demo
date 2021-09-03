#ifndef SDL2APPLICATION4_DEBUG_OVERLAY_HPP
#define SDL2APPLICATION4_DEBUG_OVERLAY_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <boost/format.hpp>

#include "../map/camera.hpp"
#include "../render/sdl-manager.hpp"
#include "../text/cached-text-renderer.hpp"
#include "../state/game-save-state.hpp"

class DebugOverlay {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::shared_ptr<Camera> _camera;
  CachedTextRenderer _textRenderer;
  GameSaveState _gameSaveState;

public:
  DebugOverlay(std::shared_ptr<SDLManager> sdlManager,
               std::shared_ptr<Camera> camera, CachedTextRenderer &textRenderer,
               GameSaveState &gameSaveState);

  void render();
};

#endif // SDL2APPLICATION4_DEBUG_OVERLAY_HPP
