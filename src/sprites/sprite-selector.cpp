#include "sprite-selector.hpp"
#include <iostream>

SpriteSelector::SpriteSelector() {}

SpriteSelector::~SpriteSelector() {}

void SpriteSelector::registerDirectionSprite(SpriteStateDirectionEnum direction,
                                             Sprite *sprite) {
  this->_sprites.insert(
      std::pair<SpriteStateDirectionEnum, Sprite *>(direction, sprite));
}

Sprite *SpriteSelector::selectSprite(SpriteState spriteState) {
  return this->_sprites[spriteState.direction];
}
