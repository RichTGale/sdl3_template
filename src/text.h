

#ifndef text_h
#define text_h

#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"

typedef struct text_data {
    TTF_Text* t;    
} text;

text* init_text(TTF_TextEngine* te, TTF_Font* f, char* txt, int r, int g, int b, int a);

bool draw_text(text* t);

void term_text(text* t);

#endif
