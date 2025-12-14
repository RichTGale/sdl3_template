add_library (gui ../../src/gui.h ../../src/gui.c)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

target_link_libraries(gui LINK_PUBLIC SDL3::SDL3)

target_include_directories (gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
