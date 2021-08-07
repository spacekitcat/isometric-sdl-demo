#ifndef SPRITE_STATE_H
#define SPRITE_STATE_H

enum SpriteStateDirectionEnum {
    North, NorthEast, East, SouthEast, South, SouthWest, West, NorthWest
};

struct SpriteState {
    SpriteStateDirectionEnum direction;
};

#endif //SPRITE_STATE_H