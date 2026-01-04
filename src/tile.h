
#ifndef tile_h
#define tile_h

#include <SDL3/SDL.h>

#include "array.h"
#include "render_target.h"

typedef struct tile_data {
    SDL_FRect rct;
    array render_targets;
} tile;

tile* init_tile(SDL_Renderer* r, TTF_TextEngine* te, int x, int y, int w, int h);

array* get_render_targets(tile* t);

void term_tile(tile* t);

#endif
