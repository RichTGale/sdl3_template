
#include "render_target.h"

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

    SDL_DestroySurface(srf);
    SDL_CloseIO(src);

    return txt;
}

render_target* init_render_target_text(TTF_TextEngine* te, int render_layer, char* font_path, char* _text)
{
    render_target* rt = (render_target*) malloc(sizeof(struct render_target_data));

    rt->render_target_type = RENDER_TARGET_TEXT;
    rt->render_layer = render_layer;
  
    rt->t = init_text(te, font_path, _text, 255, 255, 255, 255);
    
    return rt;
}

render_target* init_render_target_image(SDL_Renderer* r, int render_layer, char* img_path)
{
    render_target* rt = (render_target*) malloc(sizeof(struct render_target_data));

    rt->render_target_type = RENDER_TARGET_IMAGE;
    rt->render_layer = render_layer;
  
    rt->txt = load_img(r, img_path);

    return rt;
}

int min_heap_get_val(void* render_target_var)
{
    render_target* rt = (render_target*) render_target_var;

    return rt->render_layer;
}

void show_render_target(SDL_Renderer* r, render_target* rt)
{
    switch (rt->render_target_type)
    {
        case RENDER_TARGET_TEXT:
            if(!draw_text(rt->t))
            {
                fsout(stdout, "show_render_target() failure: draw_text() returned 0.\n");
            }
            break;
        case RENDER_TARGET_IMAGE:
            if (!SDL_RenderTexture(r, rt->txt, NULL, NULL))
            {
                fsout(stdout, "show_render_target() failure: %s\n", SDL_GetError());
            }
            break;
        default:
            fsout(stdout, "show_render_target() failure: invalid render_target_type.\n");
    }
}

void term_render_target(render_target* rt)
{
    if (rt->txt != NULL)
    {
        SDL_DestroyTexture(rt->txt);
    }

    free(rt);
}
