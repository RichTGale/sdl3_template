
#ifndef animation_h
#define animation_h

#include <SDL3/SDL.h>
#include <stdbool.h>

#include "utils.h"
#include "array.h"
#include "render_target.h"

enum AnimationTypes {
    ANIMATION_TYPE_EXAMPLE,
    ANIMATION_TYPE_NONE
};

typedef struct animation_data {
    array render_targets;
    enum AnimationTypes animation_type;
} animation;


animation* init_animation(enum AnimationTypes animation_type, SDL_Window* win, SDL_Renderer* r, TTF_TextEngine* te);

bool animation_clicked(animation ani, int x, int y);

array* get_render_targets(animation* p);

void term_animation(animation* p);

#endif
