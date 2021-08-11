#include "sprite-registry.hpp"

SpriteRegistry::SpriteRegistry(SDL_Renderer *renderer) {
  this->_renderer = renderer;
}

void SpriteRegistry::loadSprite(const std::string &path, const std::string &asKey, struct SpriteMetadata *metadata) {
    this->_tileRegistry[asKey] = new Sprite(this->_renderer,
                                            path, metadata->columns, metadata->rows);
}

Sprite *SpriteRegistry::getSprite(const std::string &key) {
  return this->_tileRegistry[key];
}
