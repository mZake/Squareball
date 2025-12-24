cmake_minimum_required(VERSION 3.15)
project(raygui VERSION 4.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(raygui "src/raygui.c" "src/raygui.h")

target_include_directories(raygui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(raygui PUBLIC raylib)
