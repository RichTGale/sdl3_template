add_executable(sdl3_template ../src/main.c)

target_link_libraries(sdl3_template PRIVATE SDL3_ttf::SDL3_ttf SDL3::SDL3)

target_link_libraries (sdl3_template LINK_PUBLIC gui)
