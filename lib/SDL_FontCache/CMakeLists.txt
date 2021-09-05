cmake_minimum_required(VERSION 3.7)
project(SDL_FontCache VERSION 0.10.0 LANGUAGES C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIR})

add_library(FontCache SDL_FontCache.h SDL_FontCache.c)
target_link_libraries(FontCache ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})
# target_include_directories(FontCache PUBLIC ${sdl2_INCLUDE_DIR})
# target_include_directories(FontCache PUBLIC .)
# target_link_libraries(FontCache ${sdl2_LIBRARY})
# target_link_libraries(FontCache ${sdl2main_LIBRARY})
# target_include_directories(FontCache PUBLIC ${sdl2_ttf_INCLUDE_DIR})
# target_link_libraries(FontCache ${sdl2_ttf_LIBRARY})

# add_executable(FontCache-tests
# 	test/main.c
# )
# file(COPY test/utf8_sample.txt DESTINATION ${CMAKE_BINARY_DIR})
# file(COPY test/fonts/FreeSans.ttf DESTINATION ${CMAKE_BINARY_DIR}/fonts)
# target_link_libraries(FontCache-tests FontCache)


