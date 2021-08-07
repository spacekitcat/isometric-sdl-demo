#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../sprites/sprite.hpp"

unsigned int Factorial( unsigned int number ) {
    return number > 1 ? Factorial(number-1)*number : 1;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "Image slicer works", "[factorial]" ) {
    SDL_Window *screen = SDL_CreateWindow(
      "Test app", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, 100, 100,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *surface = SDL_CreateRGBSurface(0, 8, 8, 32, 0, 0, 0, 255);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
}