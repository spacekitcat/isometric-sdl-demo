#include "sprite-selector.hpp"

SpriteSelector::SpriteSelector() {}

SpriteSelector::~SpriteSelector() {
  std::cout << "Destroying SpriteSelector" << std::endl;
  this->_sprites.clear();
}

void SpriteSelector::registerDirectionSprite(SpriteStateDirectionEnum direction,
                                             std::shared_ptr<Sprite> sprite) {
  this->_sprites.insert(
      std::pair<SpriteStateDirectionEnum, std::shared_ptr<Sprite>>(direction,
                                                                   sprite));
  sprite->setRenderBoundingBox(true);
}

std::shared_ptr<Sprite> SpriteSelector::selectSprite(SpriteState spriteState) {
  return this->_sprites[spriteState.direction];
}
