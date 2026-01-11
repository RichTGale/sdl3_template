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
    if ((g->w = SDL_CreateWindow("mywindow", w, h, SDL_WINDOW_FULLSCREEN)) != NULL)
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
 * This function has the main game loop in it.
 */
gui* exec_gui(gui* g)
{
    SDL_Event event; // Stores input
    const long long FRAMES_PER_SEC = 60; // Frames per second.
    long long nanos_per_sec; // #define in timer_nano.h
    long long frame_len;   // The number of nanoseconds per frame 
    bool running = true; // Whether the program should be running.
     
    /* Calculate the length of a frame in nanoseconds. */
    nanos_per_sec = NANOS_PER_SEC; // #define in timer_nano.h
    frame_len = nanos_per_sec / FRAMES_PER_SEC;

    /* Create some animations and add them to the array of animations. */
    array_init(&(g->animations));
    array_push_back(&(g->animations), (void*) init_animation(ANIMATION_TYPE_BASICS, g->w, g->r, g->te));
//    array_push_back(&(g->animations), (void*) init_animation(ANIMATION_TYPE_FLASHER, g->w, g->r, g->te));
//    array_push_back(&(g->animations), (void*) init_animation(ANIMATION_TYPE_PEAK, g->w, g->r, g->te));
    
    /* Main game loop. */
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
                    /* Exit the program if the mouse button is released on the example button. */
                    case SDL_EVENT_MOUSE_BUTTON_UP:
                        for (int i = 0; i < array_size(g->animations); i++)
                        {
                            if (animation_clicked((animation*) array_get_data(g->animations, i), event.motion.x, event.motion.y))
                            {
                                running = false;
                            }
                        }
                        break;

                    case SDL_EVENT_MOUSE_MOTION:
                        for (int i = 0; i < array_size(g->animations); i++)
                        {
                            animation_hovered((animation*) array_get_data(g->animations, i), event.motion.x, event.motion.y);
                        }
                        break;

                }
            }
            
            for (int i = 0; i < array_size(g->animations); i++)
            {
                animation_run((animation*) array_get_data(g->animations, i));
            }

            /* Put all the render_targets from all the animations into the heap.. */
            populate_rendering_heap(g);

            /* Clear the screen. */
            SDL_RenderClear(g->r);

            /* Empty the heap and draw all the stuff in it. */
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

    /* Clean up the animation. */
    for (int i = 0; i < array_size(g->animations); i++)
    {
        term_animation(array_get_data(g->animations, i));
    }
    array_free(&(g->animations));

    /* Return the gui. */
    return g;
}

/**
 * Put all the render_targets from all the animations into the heap.. 
 */
void populate_rendering_heap(gui* g)
{
    for (int i = 0; i < array_size(g->animations); i++)
    {
        for (int j = 0; j < array_size(*(get_render_targets(array_get_data(g->animations, i)))); j++)
        {
            if (!min_heap_val_exists(g->render_targets, (void*) array_get_data(*(get_render_targets(array_get_data(g->animations, i))), j)))
            {
                min_heap_add(&(g->render_targets), (void*) array_get_data(*(get_render_targets(array_get_data(g->animations, i))), j));
            }
        }
    }
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
