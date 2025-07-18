cmake_minimum_required(VERSION 3.15)
project(Squareball VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(External/raylib)
add_subdirectory(External/raygui)

set(GAME_SOURCES
    Source/States/Match.cpp
    Source/States/Match.h
    Source/Collision.cpp
    Source/Collision.h
    Source/Entity.h
    Source/Game.cpp
    Source/Game.h
    Source/Main.cpp
    Source/Render.cpp
    Source/Render.h
    Source/State.cpp
    Source/State.h
)

add_executable(Game ${GAME_SOURCES})

target_include_directories(Game PRIVATE Source)
target_link_libraries(Game PRIVATE raylib raygui)

set_target_properties(Game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
