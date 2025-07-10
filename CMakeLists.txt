cmake_minimum_required(VERSION 3.15)
project(Squareball VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("External/raylib")
add_subdirectory("External/raygui")

file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h")
add_executable(Game ${SOURCES})

target_include_directories(Game PRIVATE "Source")
target_link_libraries(Game PRIVATE raylib raygui)

set_target_properties(Game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
