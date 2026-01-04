cmake_minimum_required(VERSION 3.16)
project(sdl3_template)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(SDLTTF_VENDORED ON)

add_subdirectory(vendored/SDL3-3.2.10 EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL3_ttf-3.2.2 EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL3_image-3.2.4 EXCLUDE_FROM_ALL)
add_subdirectory(lib)
add_subdirectory(bin)

