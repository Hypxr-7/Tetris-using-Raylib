cmake_minimum_required(VERSION 3.26)
project(Tetris-using-Raylib)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib REQUIRED) # QUIET or REQUIRED

add_executable(Tetris-using-Raylib
        src/main.cpp
        src/Game.cpp
        src/Grid.cpp
        src/Block.cpp
)

target_link_libraries(Tetris-using-Raylib raylib)