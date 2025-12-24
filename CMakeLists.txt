cmake_minimum_required(VERSION 3.15)
project(Squareball LANGUAGES CXX)

include(FetchContent)

add_subdirectory(External/raylib)
add_subdirectory(External/raygui)
add_subdirectory(External/yaml-cpp)

FetchContent_Declare(SDL3
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.2.28.zip
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    FIND_PACKAGE_ARGS 3.2.28 QUIET)

FetchContent_MakeAvailable(SDL3)

set(SOURCE_FILES
    Source/Core/app.cpp
    Source/Core/app.h
    Source/Core/Collision.cpp
    Source/Core/Collision.h
    Source/Core/Entity.cpp
    Source/Core/Entity.h
    Source/Core/Main.cpp
    Source/Core/Tilemap.cpp
    Source/Core/Tilemap.h
    Source/Core/Tileset.cpp
    Source/Core/Tileset.h
    Source/Game/Game.cpp
    Source/Game/Match.h
    Source/Game/Match.cpp)

add_executable(Squareball ${SOURCE_FILES})

set_target_properties(Squareball
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF)

target_include_directories(Squareball PRIVATE "${CMAKE_SOURCE_DIR}/Source")

target_link_libraries(Squareball PRIVATE raylib raygui SDL3::SDL3 yaml-cpp)
