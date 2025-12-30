

#ifndef rendor_target_h
#define rendor_target_h

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>

#include "text.h"
#include "utils.h"

enum rendor_target_types {
    RENDOR_TARGET_TEXT,
    RENDOR_TARGET_IMAGE
};

typedef struct rendor_target_data {
    SDL_Texture* txt;
    SDL_FRect src;
    SDL_FRect dst;
    text* t;
    enum rendor_target_types rendor_target_type;
    unsigned int rendor_layer;
} rendor_target;

rendor_target* init_rendor_target(SDL_Renderer* r, TTF_TextEngine* te, enum rendor_target_types rendor_target_type, int rendor_layer);

int min_heap_get_val(void* rendor_target_var);

void show_rendor_target(SDL_Renderer* r, rendor_target* rt);

void term_rendor_target(rendor_target* rt);

#endif
