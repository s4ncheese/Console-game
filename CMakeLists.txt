cmake_minimum_required(VERSION 3.21)
project(Square_game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Square_game main.cpp field/field.h field/field.cpp player/player.h Cubes/cubes.h)