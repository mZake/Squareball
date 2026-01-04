set(SOURCE_FILES stb_image.cpp stb_image.h)

add_library(stb_image ${SOURCE_FILES})
add_library(stb_image::stb_image ALIAS stb_image)

target_include_directories(stb_image PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
