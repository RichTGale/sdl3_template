
#include "render_target.h"


render_target* init_render_target_text(TTF_TextEngine* te, int render_layer, char* font_path, char* txt, int x, int y, int r, int g, int b, int a)
{
    render_target* rt = (render_target*) malloc(sizeof(struct render_target_data));
    int w, h;

    rt->render_target_type = RENDER_TARGET_TEXT;
    rt->render_layer = render_layer;
    rt->txt = init_text(te, font_path, txt, r, g, b, a);
    rt->src.x = x; rt->src.y = y;
            
    /* Get the size of the text. */
    if (!TTF_GetTextSize(rt->txt->t, &w, &h))
    {
        fsout(stdout, "init_render_target_text() failure: %s\n", SDL_GetError());
    }
    
    rt->src.w = w; rt->src.h = h;

    return rt;
}

render_target* init_render_target_image(SDL_Renderer* r, int render_layer, char* img_path, int x, int y, int w, int h)
{
    render_target* rt = (render_target*) malloc(sizeof(struct render_target_data));

    rt->render_target_type = RENDER_TARGET_IMAGE;
    rt->render_layer = render_layer;
    rt->img = init_image(r, img_path);
    rt->src.x = x; rt->src.y = y; rt->src.w = w; rt->src.h = h;

    return rt;
}

SDL_FRect get_render_target_src(render_target rt)
{
    return rt.src;
}

int min_heap_get_val(void* render_target_var)
{
    render_target* rt = (render_target*) render_target_var;

    return rt->render_layer;
}

void draw_render_target(SDL_Renderer* r, render_target* rt)
{
    switch (rt->render_target_type)
    {
        case RENDER_TARGET_TEXT:
            if(!draw_text(rt->txt, rt->src))
            {
                fsout(stdout, "show_render_target() failure: draw_text() returned 0.\n");
            }
            break;
        case RENDER_TARGET_IMAGE:
            if(!draw_image(r, rt->src, rt->img))
            {
                fsout(stdout, "show_render_target() failure: draw_image() returned 0.\n");
            }
            break;
        default:
            fsout(stdout, "show_render_target() failure: invalid render_target_type.\n");
    }
}

void set_render_target_src(render_target* rt, int x, int y)
{
    rt->src.x = x;
    rt->src.y = y;
}

void term_render_target(render_target* rt)
{
    switch (rt->render_target_type)
    {
        case RENDER_TARGET_TEXT:
            term_text(rt->txt);
            break;
        case RENDER_TARGET_IMAGE:
            term_image(rt->img);
            break;
        default:
            fsout(stdout, "term_render_target() failure: render_target_type not specified.\n");
    }

    free(rt);
}
