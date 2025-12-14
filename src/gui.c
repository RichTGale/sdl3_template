#include "gui.h"

gui* init_gui()
{
    gui* g = (gui*) malloc(sizeof(struct gui_data));

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL init success\n");
    }
    else
    {
        printf("SDL init failure: %s\n", SDL_GetError());
    }

    if ((g->w = SDL_CreateWindow("mywindow", 1250, 720, 0)) != NULL)
    {
        printf("SDL window creation success\n");
    }
    else
    {
        printf("SDL window creation failure: %s\n", SDL_GetError());
    }

    if ((g->r = SDL_CreateRenderer(g->w, NULL)) != NULL)
    {
        printf("SDL renderer creation success\n");
    }
    else
    {
        printf("Create renderer failure: %s\n", SDL_GetError());
    }

    return g;
}

gui* exec_gui(gui* g)
{
    SDL_Event event;
    bool running = true;

    while (running)
    {
	    while(SDL_PollEvent(&event))
	    {
	        switch (event.type)
	        {
	            case SDL_EVENT_MOUSE_BUTTON_UP:
	                running = false;
	                break;
	        }
	    }
	    SDL_RenderClear(g->r);
	    SDL_RenderPresent(g->r);
    }

    return g;
}

void term_gui(gui* g)
{
    SDL_DestroyRenderer(g->r);
    SDL_DestroyWindow(g->w);
    SDL_Quit();
}
