#ifndef gui_h
#define gui_h

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct gui_data {
    SDL_Window* w;
    SDL_Renderer* r;
    SDL_Event* e;
} gui;

gui* init_gui();

gui* exec_gui(gui* g);

void term_gui(gui* g);

#endif
