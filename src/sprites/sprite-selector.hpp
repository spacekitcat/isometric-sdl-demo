#ifndef SDL2APPLICATION4_SPRITE_SELECTOR_HPP
#define SDL2APPLICATION4_SPRITE_SELECTOR_HPP

#include "sprite-state.hpp"
#include "sprite.hpp"
#include <map>

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

#endif // SDL2APPLICATION4_SPRITE_SELECTOR_HPP
