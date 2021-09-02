#ifndef SDL2APPLICATION4_SPRITE_REGISTRY_HPP
#define SDL2APPLICATION4_SPRITE_REGISTRY_HPP

#include <map>
#include <unordered_map>

#include "../render/sdl-manager.hpp"
#include "../textures/texture-wrapper-factory.hpp"
#include "sprite-metadata.hpp"
#include "sprite.hpp"

class SpriteRegistry {
private:
  TextureWrapperFactory &_textureWrapperFactory;
  std::shared_ptr<SDLManager> _sdlManager;
  std::map<std::string, Sprite *> _tileRegistry;

public:
  SpriteRegistry(std::shared_ptr<SDLManager> sdlManager,
                 TextureWrapperFactory& textureWrapperFactory);
  ~SpriteRegistry();

  void loadSprite(const std::string &path, const std::string &asKey,
                  struct SpriteMetadata *metadata);

  Sprite *getSprite(const std::string &key);
};

#endif
