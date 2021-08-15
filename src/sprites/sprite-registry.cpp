#include "sprite-registry.hpp"

SpriteRegistry::SpriteRegistry(SDLManager *sdlManager) {
  _sdlManager = sdlManager;
}

void SpriteRegistry::loadSprite(const std::string &path, const std::string &asKey, struct SpriteMetadata *metadata) {
    this->_tileRegistry[asKey] = new Sprite(_sdlManager->getRenderer(),
                                            path, metadata->columns, metadata->rows);
}

Sprite *SpriteRegistry::getSprite(const std::string &key) {
  return this->_tileRegistry[key];
}
