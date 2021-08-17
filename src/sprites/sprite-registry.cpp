#include "sprite-registry.hpp"

SpriteRegistry::SpriteRegistry() {}

SpriteRegistry::SpriteRegistry(std::shared_ptr<SDLManager> sdlManager) {
  _sdlManager = sdlManager;
}

void SpriteRegistry::loadSprite(const std::string &path,
                                const std::string &asKey,
                                struct SpriteMetadata *metadata) {
  this->_tileRegistry[asKey] = new Sprite(_sdlManager, path, metadata);
}

Sprite *SpriteRegistry::getSprite(const std::string &key) {
  return this->_tileRegistry[key];
}
