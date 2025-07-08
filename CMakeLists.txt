cmake_minimum_required(VERSION 3.15)
project(Squareball VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Download raylib if it's not already on the system
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.zip
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    FIND_PACKAGE_ARGS 5.5 QUIET
)
FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h")
add_executable(Game ${SOURCES})

target_include_directories(Game PRIVATE "Source")
target_link_libraries(Game PRIVATE raylib)

set_target_properties(Game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
