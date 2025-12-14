/**
 * gui.h
 *
 * This file contains the data structure and function prototype/declarations
 * for the gui library.
 * The gui library is a graphical application that uses SDL3.
 *
 * Date written was 14 December 2025
 * Written by Richard Gale..
 */

#ifndef gui_h
#define gui_h

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>

/**
 * This is the gui data structure.
 */
typedef struct gui_data {
    SDL_Window* w;
    SDL_Renderer* r;
    SDL_Event* e;
    TTF_TextEngine* te;
    TTF_Text* t;
    TTF_Font* f;
} gui;

/**
 * This function returns an intialised gui.
 */
gui* init_gui();

/**
 * This function runs the gui supplied to it.
 */
gui* exec_gui(gui* g);

/**
 * This function cleans up and exits the gui supplied to it.
 */
void term_gui(gui* g);

#endif
