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

    g->frame_timer = timer_nano_init();

    min_heap_init(&(g->render_targets));

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
    tile* t;
    array* t_render_targets;
    const long long FRAMES_PER_SEC = 60; // Frames per second.
    long long nanos_per_sec; // #define in timer_nano.h
    long long frame_len;
    bool running = true; // Whether the program should be running.
     
    nanos_per_sec = NANOS_PER_SEC; // #define in timer_nano.h
    frame_len = nanos_per_sec / FRAMES_PER_SEC;

    /* Initialiise first tile/page (TODO: put this in init_gui(). */
    t = init_tile(g->r, g->te, 0, 0, 800, 480);

    /* Run the program. */
    while (running)
    {
        if (timer_nano_elapsed(*(g->frame_timer), frame_len))
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

            /* Populate rendering heap. */
            t_render_targets = get_render_targets(t);
            for (int i = 0; i < array_size(*t_render_targets); i++)
            {
                if (!min_heap_val_exists(g->render_targets, (void*) array_get_data(*t_render_targets, i)))
                {
                    min_heap_add(&(g->render_targets), (void*) array_get_data(*t_render_targets, i));
                }
            }

            /* Clear the screen. */
            SDL_RenderClear(g->r);

            /* Empty the rendering heap. */
            while (!min_heap_is_empty(g->render_targets))
            {
                draw_render_target(g->r, (render_target*) min_heap_pop_min(&(g->render_targets)));
            }

            /* Render everything. */
            SDL_RenderPresent(g->r);

            /* Restart framerate timer. */
            timer_nano_reinit(g->frame_timer);
        }

    }

    /* Clean up the current tile. */
    term_tile(t);

    /* Return the gui. */
    return g;
}

/**
 * This function cleans up and exits the gui supplied to it.
 */
void term_gui(gui* g)
{
    /* Clean everything up. */
    min_heap_free(&(g->render_targets));
    timer_nano_term(g->frame_timer);
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
    fsout(stdout, "Exiting SDL3 template\n");
}
