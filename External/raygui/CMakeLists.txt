add_library(raygui src/raygui.c src/raygui.h)
target_include_directories(raygui PUBLIC src)
target_link_libraries(raygui PUBLIC raylib)
