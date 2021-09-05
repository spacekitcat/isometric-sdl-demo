#pragma once

enum SpriteStateDirectionEnum {
  North = 0,
  NorthEast = 1,
  East = 2,
  SouthEast = 3,
  South = 4,
  SouthWest = 5,
  West = 6,
  NorthWest = 7,
  Idle = 8
};

struct SpriteState {
  SpriteStateDirectionEnum direction;
};
