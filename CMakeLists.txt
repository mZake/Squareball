cmake_minimum_required(VERSION 3.15)
project(Squareball LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("External/raylib")
add_subdirectory("External/raygui")
add_subdirectory("External/yaml-cpp")

add_executable(Squareball
    "Source/Core/Collision.cpp"
    "Source/Core/Collision.h"
    "Source/Core/Entity.cpp"
    "Source/Core/Entity.h"
    "Source/Core/Main.cpp"
    "Source/Core/Tilemap.cpp"
    "Source/Core/Tilemap.h"
    "Source/Core/Tileset.cpp"
    "Source/Core/Tileset.h"
    "Source/Game/Game.cpp"
    "Source/Game/Match.h"
    "Source/Game/Match.cpp"
)

target_include_directories(Squareball PRIVATE "${CMAKE_SOURCE_DIR}/Source")
target_link_libraries(Squareball PRIVATE raylib raygui yaml-cpp)

set_target_properties(Squareball PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
