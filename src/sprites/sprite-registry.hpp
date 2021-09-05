#pragma once

#include <map>
#include <unordered_map>

#include "../render/sdl-manager.hpp"
#include "sprite-metadata.hpp"
#include "sprite.hpp"

class SpriteRegistry {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::map<std::string, Sprite *> _tileRegistry;

public:
  SpriteRegistry();

  SpriteRegistry(std::shared_ptr<SDLManager> sdlManager);

  void loadSprite(const std::string &path, const std::string &asKey,
                  struct SpriteMetadata *metadata);

  Sprite *getSprite(const std::string &key);
};
