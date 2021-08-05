cmake_minimum_required(VERSION 3.7)

project(SDL2Application4)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_MIXER REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})

add_executable(SDL2Test src/Main.cpp src/spritesheets/spritesheet.cpp)
target_link_libraries(SDL2Test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

find_package(Catch2 REQUIRED)
add_executable(tests src/test/test.cpp src/spritesheets/spritesheet.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

include(CTest)
include(Catch)
catch_discover_tests(tests)

file(GLOB ASSETS
  "assets/*"
)
file(COPY ${ASSETS} DESTINATION assets)


