cmake_minimum_required(VERSION 3.30)

# Automatically set project name to the folder name
get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)
project(Endless_Dungeon C)

set(CMAKE_C_STANDARD 11)

# Set Raylib directory path
set(RAYLIB_DIR "D:/joshua_aroka/raylib/raylib/src")

# Include Raylib
include_directories(${RAYLIB_DIR})
link_directories(${RAYLIB_DIR})


# Add the executable using the dynamically set project name
add_executable(Endless_Dungeon main.c)

# Link Raylib and required system libraries
target_link_libraries(Endless_Dungeon raylib opengl32 gdi32 winmm)
