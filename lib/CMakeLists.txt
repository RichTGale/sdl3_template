add_library (utils ../../src/utils.h ../../src/utils.c)
add_library (text ../../src/text.h ../../src/text.c)
add_library (gui ../../src/gui.h ../../src/gui.c)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

target_link_libraries(text LINK_PUBLIC SDL3::SDL3 utils)
target_link_libraries(gui LINK_PUBLIC SDL3::SDL3 utils text)

target_include_directories (gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
