cmake_minimum_required(VERSION 3.7)
project(PerlinNoise VERSION 2.1 LANGUAGES CXX)

add_library(PerlinNoise SHARED PerlinNoise.hpp)
SET_TARGET_PROPERTIES(PerlinNoise PROPERTIES LINKER_LANGUAGE CXX)