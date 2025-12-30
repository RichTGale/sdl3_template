/**
 * gui.c
 *
 * This file contains the function definitions for the gui library.
 * The gui library is a graphical application that uses SDL3.
 *
 * Date written was 14 December 2025
 * Written by Richard Gale..
 */

#include "gui.h"

/**
 * This function returns an intialised gui.
 */
gui* init_gui(int w, int h)
{
    /* Allocate memory. */
    gui* g = (gui*) malloc(sizeof(struct gui_data));

    /* Initialise SDL3. */
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        fsout(stdout, "SDL init success\n");
    }
    else
    {
        fsout(stdout, "SDL init failure: %s\n", SDL_GetError());
    }

    /* Create an SDL3 window. */
    if ((g->w = SDL_CreateWindow("mywindow", w, h, 0)) != NULL)
    {
        fsout(stdout, "SDL window creation success\n");
    }
    else
    {
        fsout(stdout, "SDL window creation failure: %s\n", SDL_GetError());
    }

    /* Create an SDL3 renderer. */
    if ((g->r = SDL_CreateRenderer(g->w, NULL)) != NULL)
    {
        fsout(stdout, "SDL software renderer creation success\n");
    }
    else
    {
        fsout(stdout, "Create software renderer failure: %s\n", SDL_GetError());
    }

    g->use_ttf = false;

    min_heap_init(&(g->rendor_targets));

    /* Return the gui. */
    return g;
}

/**
 * This function initialises SDL_ttf.
 */
gui* init_ttf(gui* g)
{
    /* Initialise SDL_ttf. */
    if (TTF_Init())
    {
        fsout(stdout, "TTF initialisation success\n");
    }
    else
    {
        fsout(stdout, "TTF initialisation failure: %s\n", SDL_GetError());
    }

    /* Create an SDL3 text engine. */
    if ((g->te = TTF_CreateRendererTextEngine(g->r)) != NULL)
    {
        fsout(stdout, "TTF text engine creation success\n");
    }
    else
    {
        fsout(stdout, "TTF text engine creation failure: %s\n", SDL_GetError());
    }

    g->use_ttf = true;

    /* Return the gui. */
    return g;
}


/**
 * This function runs the gui supplied to it.
 */
gui* exec_gui(gui* g)
{
    SDL_Event event; // Stores input
    rendor_target* test_image;
    rendor_target* test_text;
    bool running = true; // Whether the program should be running.
        
    /* TODO: make each rendor_target a property of the gui. */
    test_image = init_rendor_target(g->r, g->te, RENDOR_TARGET_IMAGE, 0);
    test_text  = init_rendor_target(g->r, g->te, RENDOR_TARGET_TEXT, 1);

    /* Run the program. */
    while (running)
    {
        /* Store input events. */
	    while(SDL_PollEvent(&event))
	    {
            /* Determine what type of event happened. */
	        switch (event.type)
	        {
                /* Exit the program if the mouse button is released. */
	            case SDL_EVENT_MOUSE_BUTTON_UP:
	                running = false;
	                break;
	        }
	    }

    
	    if (!min_heap_val_exists(g->rendor_targets, (void*) test_image))
	    {
	        min_heap_add(&(g->rendor_targets), (void*) test_image);
	    }
	    if (!min_heap_val_exists(g->rendor_targets, (void*) test_text))
	    {
	        min_heap_add(&(g->rendor_targets), (void*) test_text);
	    }

        /* Render the program. */
        SDL_RenderClear(g->r);

        while (!min_heap_is_empty(g->rendor_targets))
        {
            show_rendor_target(g->r, (rendor_target*) min_heap_pop_min(&(g->rendor_targets)));
        }

	    
        SDL_RenderPresent(g->r);
        

    }
        
    term_rendor_target(test_image);
    term_rendor_target(test_text);

    /* Return the gui. */
    return g;
}

/**
 * This function cleans up and exits the gui supplied to it.
 */
void term_gui(gui* g)
{

    min_heap_free(&(g->rendor_targets));

    /* Clean everything up. */
    if (g->use_ttf)
    {
        fsout(stdout, "Cleaning TTF\n");
        TTF_DestroyRendererTextEngine(g->te);
    }

    fsout(stdout, "Cleaning SDL\n");
    SDL_DestroyRenderer(g->r);
    SDL_DestroyWindow(g->w);
    SDL_Quit();
    
    /* Print status message. */
    fsout(stdout, "Exiting gui\n");
}
