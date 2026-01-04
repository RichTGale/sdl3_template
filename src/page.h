
#ifndef page_h
#define page_h

#include <SDL3/SDL.h>
#include <string.h> // strlen()

#include "utils.h"
#include "array.h"
#include "render_target.h"

enum GuiPages {
    EXAMPLE_PAGE
};

typedef struct page_data {
    array render_targets;
    enum GuiPages gui_page;
} page;


page* init_page(enum GuiPages gui_page, SDL_Window* win, SDL_Renderer* r, TTF_TextEngine* te);

array* get_render_targets(page* p);

void term_page(page* p);

#endif
