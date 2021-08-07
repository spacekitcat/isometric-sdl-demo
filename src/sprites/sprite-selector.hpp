#ifndef SDL2APPLICATION4_SPRITE_SELECTOR_HPP
#define SDL2APPLICATION4_SPRITE_SELECTOR_HPP

#include <map>
#include "sprite.hpp"
#include "sprite-state.hpp"

class SpriteSelector {
    private:
        std::map<SpriteStateDirectionEnum, Sprite*> _sprites;

    public:
        SpriteSelector();
        ~SpriteSelector();

        void setDirectionSprite(SpriteStateDirectionEnum direction, Sprite *sprite);

        Sprite* selectSprite(SpriteState spriteState);
};

#endif //SDL2APPLICATION4_SPRITE_SELECTOR_HPP
