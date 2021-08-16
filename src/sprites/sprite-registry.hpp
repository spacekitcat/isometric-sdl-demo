#ifndef SDL2APPLICATION4_SPRITE_REGISTRY_HPP
#define SDL2APPLICATION4_SPRITE_REGISTRY_HPP

#include <unordered_map>
#include <map>

#include "sprite-metadata.hpp"
#include "sprite.hpp"
#include "../render/sdl-manager.hpp"

class SpriteRegistry {
private:
  std::shared_ptr<SDLManager> _sdlManager;
  std::map<std::string, Sprite*> _tileRegistry;

public:
  SpriteRegistry();

  SpriteRegistry(std::shared_ptr<SDLManager> sdlManager);

  void loadSprite(const std::string& path, const std::string& asKey, struct SpriteMetadata *metadata);

  Sprite* getSprite(const std::string& key);
};

#endif
