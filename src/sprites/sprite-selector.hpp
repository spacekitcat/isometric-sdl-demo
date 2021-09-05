#pragma once

#include <iostream>
#include <map>

#include "sprite-state.hpp"
#include "sprite.hpp"

class SpriteSelector {
private:
  std::map<SpriteStateDirectionEnum, Sprite *> _sprites;

public:
  SpriteSelector();
  ~SpriteSelector();

  void registerDirectionSprite(SpriteStateDirectionEnum direction,
                               Sprite *sprite);

  Sprite *selectSprite(SpriteState spriteState);
};
