cmake_minimum_required(VERSION 3.15)
project(Squareball LANGUAGES CXX)

include(FetchContent)

add_subdirectory(external/raylib)
add_subdirectory(external/raygui)
add_subdirectory(external/yaml-cpp)

FetchContent_Declare(SDL3
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.2.28.zip
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    FIND_PACKAGE_ARGS 3.2.28 QUIET)

FetchContent_MakeAvailable(SDL3)

set(SOURCE_FILES
    source/app.cpp
    source/app.h
    source/collision.cpp
    source/collision.h
    source/entity.cpp
    source/entity.h
    source/main.cpp
    source/match.cpp
    source/match.h
    source/scene.cpp
    source/scene.h
    source/tilemap.cpp
    source/tilemap.h
    source/tileset.cpp
    source/tileset.h)

add_executable(Squareball ${SOURCE_FILES})

set_target_properties(Squareball
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF)

target_include_directories(Squareball PRIVATE "${CMAKE_SOURCE_DIR}/source")

target_link_libraries(Squareball PRIVATE raylib raygui SDL3::SDL3 yaml-cpp)
