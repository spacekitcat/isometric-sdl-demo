#include "direction-input-helpers.hpp"

bool DirectionInputHelpers::isNorthPressed(const Uint8 *state) {
  return state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W];
}

bool DirectionInputHelpers::isSouthPressed(const Uint8 *state) {
  return state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S];
}

bool DirectionInputHelpers::isEastPressed(const Uint8 *state) {
  return state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D];
}

bool DirectionInputHelpers::isWestPressed(const Uint8 *state) {
  return state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A];
}

bool DirectionInputHelpers::isNorthWestPressed(const Uint8 *state) {
  return isNorthPressed(state) &&
         isWestPressed(state);
}

bool DirectionInputHelpers::isNorthEastPressed(const Uint8 *state) {
  return isNorthPressed(state) &&
         isEastPressed(state);
}

bool DirectionInputHelpers::isSouthWestPressed(const Uint8 *state) {
  return isSouthPressed(state) &&
         isWestPressed(state);
}

bool DirectionInputHelpers::isSouthEastPressed(const Uint8 *state) {
  return isSouthPressed(state) &&
         isEastPressed(state);
}

bool DirectionInputHelpers::noKeysPressed(const Uint8 *state) {
  return !(DirectionInputHelpers::isNorthWestPressed(state) ||
           DirectionInputHelpers::isNorthEastPressed(state) ||
           DirectionInputHelpers::isSouthWestPressed(state) ||
           DirectionInputHelpers::isSouthEastPressed(state) ||
           DirectionInputHelpers::isNorthPressed(state) ||
           DirectionInputHelpers::isSouthPressed(state) ||
           DirectionInputHelpers::isEastPressed(state) ||
           DirectionInputHelpers::isWestPressed(state));
}

SpriteStateDirectionEnum DirectionInputHelpers::getInputDirection(const Uint8 *state) {
  if (DirectionInputHelpers::isNorthWestPressed(state)) {
    return NorthWest;
  } else if (DirectionInputHelpers::isNorthEastPressed(state)) {
    return NorthEast;
  } else if (DirectionInputHelpers::isSouthWestPressed(state)) {
    return SouthWest;
  } else if (DirectionInputHelpers::isSouthEastPressed(state)) {
    return SouthEast;
  } else if (DirectionInputHelpers::isSouthPressed(state)) {
    return South;
  } else if (DirectionInputHelpers::isNorthPressed(state)) {
    return North;
  } else if (DirectionInputHelpers::isEastPressed(state)) {
    return East;
  } else if (DirectionInputHelpers::isWestPressed(state)) {
    return West;
  } else {
    return Idle;
  }
}