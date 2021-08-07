#ifndef SPRITESTATE_H
#define SPRITESTATE_H

enum SpriteStateDirectionEnum {
    North, NorthEast, East, SouthEast, South, SouthWest, West, NorthWest
};

struct SpriteState {
    SpriteStateDirectionEnum direction;
};

#endif