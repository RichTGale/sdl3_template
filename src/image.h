

#ifndef image_h
#define image_h

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"

typedef struct image_data {
    SDL_Texture* txr;
    char* file;
} image;

image* init_image(SDL_Renderer* r, const char* file);

bool draw_image(SDL_Renderer* r, SDL_FRect dst, image* img);

void term_image(image* img);

#endif
