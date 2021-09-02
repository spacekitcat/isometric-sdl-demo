set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wno-narrowing)
cmake_minimum_required(VERSION 3.7)

project(SDL2Application4)

# https://cmake.org/cmake/help/git-master/module/FindBoost.html
find_package(Boost REQUIRED)

# This comes in with `brew install catch2`, which (sort of) ironically creates a
# Catch /22/ since the check for Catch2 can't work unless Catch2 is installed.
# Ultimately, it should do what I need, although the error message might be less
# clear than it could be. TODO: See about packaging FindCatch2.cmake with thea app.
find_package(Catch2 REQUIRED)

# Included under ./cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_MIXER REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIR})
include_directories(include/)

add_executable(SDL2Test src/render/sdl-manager.cpp src/text/text-renderer.cpp src/textures/texture-wrapper.cpp src/state/game-save-state.cpp src/render/sdl-manager.hpp src/Main.cpp src/debug/debug-overlay.cpp src/sprites/sprite.cpp src/sprites/sprite-selector.cpp src/sprites/sprite-selector.hpp src/input/direction-input-helpers.cpp src/input/direction-input-helpers.hpp src/map/isometric-tile-map-sector.cpp src/map/isometric-tile-map-sector.hpp src/sprites/sprite-registry.cpp src/sprites/sprite-registry.hpp src/sprites/sprite-metadata.hpp src/map/coordinate-mapper.cpp src/map/coordinate-mapper.hpp src/util/pair-operators.cpp src/util/pair-operators.hpp src/debug/debug-draw-utils.cpp src/debug/debug-draw-utils.hpp src/map/Camera.cpp)
target_link_libraries(SDL2Test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2TTF_LIBRARY} ${Boost_LIBRARIES})

# BEGIN: Test setup
add_executable(tests src/render/sdl-manager.cpp src/render/sdl-manager.hpp src/test/test.cpp src/sprites/sprite.cpp src/util/pair-operators.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${Boost_LIBRARIES})

include(CTest)
include(Catch)
catch_discover_tests(tests)

file(GLOB ASSETS
  "assets/*"
)
# END: Test setup

file(COPY ${ASSETS} DESTINATION assets)


