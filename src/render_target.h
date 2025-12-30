

#ifndef render_target_h
#define render_target_h

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>

#include "text.h"
#include "utils.h"

enum render_target_types {
    RENDER_TARGET_TEXT,
    RENDER_TARGET_IMAGE
};

typedef struct render_target_data {
    SDL_Texture* txt;
    SDL_FRect src;
    SDL_FRect dst;
    text* t;
    enum render_target_types render_target_type;
    unsigned int render_layer;
} render_target;

render_target* init_render_target_text(TTF_TextEngine* te, int render_layer, char* font_path, char* text);
render_target* init_render_target_image(SDL_Renderer* r, int render_layer, char* img_path);

int min_heap_get_val(void* render_target_var);

void show_render_target(SDL_Renderer* r, render_target* rt);

void term_render_target(render_target* rt);

#endif
