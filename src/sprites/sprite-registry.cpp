#include "sprite-registry.hpp"

SpriteRegistry::SpriteRegistry() {}

SpriteRegistry::SpriteRegistry(std::shared_ptr<SDLManager> sdlManager) {
  _sdlManager = sdlManager;
}

SpriteRegistry::~SpriteRegistry() {
  std::cout << "Destroying SpriteRegistry" << std::endl;
  _tileRegistry.clear();
}

void SpriteRegistry::loadSprite(const std::string &path,
                                const std::string &asKey,
                                struct SpriteMetadata *metadata) {
  auto sprite = make_shared<Sprite>(_sdlManager);
  sprite->setSpritesheet(path, metadata);
  this->_tileRegistry[asKey] = sprite;
}

std::shared_ptr<Sprite> SpriteRegistry::getSprite(const std::string &key) {
  return this->_tileRegistry[key];
}
