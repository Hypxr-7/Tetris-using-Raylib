cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
set(CMAKE_CXX_STANDARD 20)

project(Tetris-using-Raylib)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Our Project

add_executable(${PROJECT_NAME} src/main.cpp src/Grid.cpp src/Block.cpp src/Game.cpp)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

configure_file(assets/bgm/bgm-track-1.mp3 assets/bgm/bgm-track-1.mp3 COPYONLY)
configure_file(assets/fonts/SpaceMono.ttf assets/fonts/SpaceMono.ttf COPYONLY)
configure_file(assets/highscores/scores.txt assets/highscores/scores.txt COPYONLY)
configure_file(assets/images/bg.png assets/images/bg.png COPYONLY)
configure_file(assets/sfx/row-cleared.mp3 assets/sfx/row-cleared.mp3 COPYONLY)