cmake_minimum_required(VERSION 3.15)
project(raygui VERSION 4.0 LANGUAGES C)

add_library(raygui src/raygui.c src/raygui.h)

target_include_directories(raygui PUBLIC src)
target_link_libraries(raygui PUBLIC raylib)
