#pragma once

#include <iostream>
#include <map>

#include "sprite-state.hpp"
#include "sprite.hpp"

class SpriteSelector {
private:
  std::map<SpriteStateDirectionEnum, std::shared_ptr<Sprite>> _sprites;

public:
  SpriteSelector();
  ~SpriteSelector();

  void registerDirectionSprite(SpriteStateDirectionEnum direction,
                               std::shared_ptr<Sprite> sprite);

  std::shared_ptr<Sprite> selectSprite(SpriteState spriteState);
};
