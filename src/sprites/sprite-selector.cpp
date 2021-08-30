#include "sprite-selector.hpp"

SpriteSelector::SpriteSelector() {}

SpriteSelector::~SpriteSelector() {}

void SpriteSelector::registerDirectionSprite(SpriteStateDirectionEnum direction,
                                             Sprite *sprite) {
  this->_sprites.insert(
      std::pair<SpriteStateDirectionEnum, Sprite *>(direction, sprite));
  sprite->setRenderBoundingBox(true);
}

Sprite *SpriteSelector::selectSprite(SpriteState spriteState) {
  return this->_sprites[spriteState.direction];
}
