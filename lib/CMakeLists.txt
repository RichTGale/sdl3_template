add_library (utils ../../src/utils.h ../../src/utils.c)
add_library (array ../../src/array.h ../../src/array.c)
add_library (text ../../src/text.h ../../src/text.c)
add_library (image ../../src/image.h ../../src/image.c)
add_library (render_target ../../src/render_target.h ../../src/render_target.c)
add_library (min_heap ../../src/min_heap.h ../../src/min_heap.c)
add_library (gui ../../src/gui.h ../../src/gui.c)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

target_link_libraries(text LINK_PUBLIC SDL3::SDL3 utils)
target_link_libraries(render_target LINK_PUBLIC SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf image text utils)
target_link_libraries(min_heap LINK_PUBLIC render_target array)
target_link_libraries(gui LINK_PUBLIC SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf utils render_target min_heap)

target_include_directories (gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
