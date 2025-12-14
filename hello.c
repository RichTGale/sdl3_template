#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    bool running = true;

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL init success\n");
    }
    else
    {
        printf("SDL init failure: %s\n", SDL_GetError());
    }

    if ((window = SDL_CreateWindow("mywindow", 1250, 720, 0)) != NULL)
    {
        printf("SDL window creation success\n");
    }
    else
    {
        printf("SDL window creation failure: %s\n", SDL_GetError());
    }

    if ((renderer = SDL_CreateRenderer(window, NULL)) != NULL)
    {
        printf("SDL renderer creation success\n");
    }
    else
    {
        printf("Create renderer failure: %s\n", SDL_GetError());
    }

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
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
