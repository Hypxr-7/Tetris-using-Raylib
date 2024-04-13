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

configure_file(assets/bgm/bgm-track-1.mp3 assets/bgm/bgm-track-1.mp3 COPYONLY)

target_link_libraries(Tetris-using-Raylib raylib)