

#ifndef text_h
#define text_h

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"

typedef struct text_data {
    TTF_Text* t;
    TTF_Font* f;
} text;

text* init_text(TTF_TextEngine* te, char* font_path, char* txt, int r, int g, int b, int a);

bool draw_text(text* t, SDL_FRect src);

void term_text(text* t);

#endif
