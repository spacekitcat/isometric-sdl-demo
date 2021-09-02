#include "sprite-registry.hpp"

SpriteRegistry::SpriteRegistry(std::shared_ptr<SDLManager> sdlManager,
                               TextureWrapperFactory& textureWrapperFactory)
    : _sdlManager(sdlManager), _textureWrapperFactory(textureWrapperFactory) {
}

SpriteRegistry::~SpriteRegistry() {}

void SpriteRegistry::loadSprite(const std::string &path,
                                const std::string &asKey,
                                struct SpriteMetadata *metadata) {
  auto sprite = new Sprite(_sdlManager, _textureWrapperFactory);
  sprite->setSpritesheet(path, metadata);
  this->_tileRegistry[asKey] = sprite;
}

Sprite *SpriteRegistry::getSprite(const std::string &key) {
  return this->_tileRegistry[key];
}
