#ifndef SDL2APPLICATION4_DEBUG_OVERLAY_HPP
#define SDL2APPLICATION4_DEBUG_OVERLAY_HPP

#include <SDL_ttf.h>
#include <SDL.h>
#include <boost/format.hpp>

#include "../map/camera.hpp"
#include "../render/sdl-manager.hpp"

class DebugOverlay {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::shared_ptr<Camera> _camera;
  TTF_Font *_font;

  void renderText(std::string text);

public:
  DebugOverlay(std::shared_ptr<SDLManager> sdlManager, std::shared_ptr<Camera> camera);

  void render();
};


#endif //SDL2APPLICATION4_DEBUG_OVERLAY_HPP
