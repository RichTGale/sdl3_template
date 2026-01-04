
#ifndef page_h
#define page_h

#include <SDL3/SDL.h>

#include "utils.h"
#include "array.h"
#include "render_target.h"

enum GuiPages {
    EXAMPLE_PAGE
};

typedef struct page_data {
    array rects;
    array render_targets;
} page;


page* init_page(enum GuiPages gui_page, SDL_Renderer* r, TTF_TextEngine* te, int x, int y, int w, int h);

array* get_render_targets(page* p);

void term_page(page* p);

#endif
