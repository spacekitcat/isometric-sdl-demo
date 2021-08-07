#ifndef SDL2APPLICATION4_DIRECTION_INPUT_HELPERS_HPP
#define SDL2APPLICATION4_DIRECTION_INPUT_HELPERS_HPP

#include <SDL.h>

class DirectionInputHelpers {
public:
  static bool isNorthPressed(const Uint8 *state);

  static bool isEastPressed(const Uint8 *state);

  static bool isSouthPressed(const Uint8 *state);

  static bool isWestPressed(const Uint8 *state);

  static bool isNorthWestPressed(const Uint8 *state);

  static bool isNorthEastPressed(const Uint8 *state);

  static bool isSouthWestPressed(const Uint8 *state);

  static bool isSouthEastPressed(const Uint8 *state);

  static bool noKeysPressed(const Uint8 *state);
};


#endif //SDL2APPLICATION4_DIRECTION_INPUT_HELPERS_HPP
