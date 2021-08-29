#ifndef SDL2APPLICATION4_DEBUG_OVERLAY_HPP
#define SDL2APPLICATION4_DEBUG_OVERLAY_HPP

#include <SDL_ttf.h>
#include <SDL.h>
#include <boost/format.hpp>

#include "../map/camera.hpp"
#include "../render/sdl-manager.hpp"
#include "../text/text-renderer.hpp"

class DebugOverlay {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::shared_ptr<Camera> _camera;
  TextRenderer _textRenderer;

  void renderText(std::string text);

public:
  DebugOverlay(std::shared_ptr<SDLManager> sdlManager, std::shared_ptr<Camera> camera, TextRenderer &textRenderer);

  void render();
};


#endif //SDL2APPLICATION4_DEBUG_OVERLAY_HPP
