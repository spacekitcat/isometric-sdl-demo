#pragma once

#include <iostream>
#include <map>
#include <unordered_map>

#include "../render/sdl-manager.hpp"
#include "sprite-metadata.hpp"
#include "sprite.hpp"

class SpriteRegistry {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::map<std::string, std::shared_ptr<Sprite>> _tileRegistry;

public:
  SpriteRegistry();
  ~SpriteRegistry();

  SpriteRegistry(std::shared_ptr<SDLManager> sdlManager);

  void loadSprite(const std::string &path, const std::string &asKey,
                  struct SpriteMetadata *metadata);

  std::shared_ptr<Sprite> getSprite(const std::string &key);
};
