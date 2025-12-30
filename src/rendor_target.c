
#include "rendor_target.h"

SDL_Texture* load_img(SDL_Renderer* r, char* fname)
{
    SDL_IOStream* src;
    SDL_Surface* srf;
    SDL_Texture* txt;
    
    if ((src = SDL_IOFromFile(fname, "r")) == NULL)
    {
        fsout(stdout, "load_img() failure: %s\n", SDL_GetError());
    }
    if ((srf = IMG_LoadJPG_IO(src)) == NULL)
    {
        fsout(stdout, "load_img() failure: Unable to load jpg!\n");
    }
    if ((txt = SDL_CreateTextureFromSurface(r, srf)) == NULL)
    {
        fsout(stdout, "load_img() failure: %s\n", SDL_GetError());
    }

    return txt;
}

rendor_target* init_rendor_target(SDL_Renderer* r, TTF_TextEngine* te, enum rendor_target_types rendor_target_type, int rendor_layer)
{
    rendor_target* rt = (rendor_target*) malloc(sizeof(struct rendor_target_data));

    rt->rendor_target_type = rendor_target_type;
    rt->rendor_layer = rendor_layer;
  
    if (rt->rendor_target_type == RENDOR_TARGET_TEXT)
    {
        rt->t = init_text(te, "./fonts/Inconsolata-Regular.ttf", "Click the mouse to exit.", 255, 255, 255, 255);
    }
    if (rt->rendor_target_type == RENDOR_TARGET_IMAGE)
    {
        rt->txt = load_img(r, "./img/test.jpg");
    }

//    rt->src;
//    rt->dst;

    return rt;
}

int min_heap_get_val(void* rendor_target_var)
{
    rendor_target* rt = (rendor_target*) rendor_target_var;

    return rt->rendor_layer;
}

void show_rendor_target(SDL_Renderer* r, rendor_target* rt)
{
    switch (rt->rendor_target_type)
    {
        case RENDOR_TARGET_TEXT:
            if(!draw_text(rt->t))
            {
                fsout(stdout, "show_rendor_target() failure: draw_text() returned 0.\n");
            }
            break;
        case RENDOR_TARGET_IMAGE:
            if (!SDL_RenderTexture(r, rt->txt, NULL, NULL))
            {
                fsout(stdout, "show_render_target() failure: %s\n", SDL_GetError());
            }
            break;
        default:
            fsout(stdout, "show_rendor_target() failure: invalid rendor_target_type.\n");
    }
}

void term_rendor_target(rendor_target* rt)
{
    if (rt->txt != NULL)
    {
        SDL_DestroyTexture(rt->txt);
    }

    free(rt);
}
