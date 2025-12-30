
#include "render_target.h"


render_target* init_render_target_text(TTF_TextEngine* te, int render_layer, char* font_path, char* txt, int x, int y, int r, int g, int b, int a)
{
    render_target* rt = (render_target*) malloc(sizeof(struct render_target_data));

    rt->render_target_type = RENDER_TARGET_TEXT;
    rt->render_layer = render_layer;
    rt->txt = init_text(te, font_path, txt, r, g, b, a);
    rt->x = x;
    rt->y = y;

    return rt;
}

render_target* init_render_target_image(SDL_Renderer* r, int render_layer, char* img_path, int x, int y)
{
    render_target* rt = (render_target*) malloc(sizeof(struct render_target_data));

    rt->render_target_type = RENDER_TARGET_IMAGE;
    rt->render_layer = render_layer;
    rt->img = init_image(r, img_path);
    rt->x = x;
    rt->y = y;

    return rt;
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
            if(!draw_text(rt->txt, rt->x, rt->y))
            {
                fsout(stdout, "show_render_target() failure: draw_text() returned 0.\n");
            }
            break;
        case RENDER_TARGET_IMAGE:
            if(!draw_image(r, rt->img))
            {
                fsout(stdout, "show_render_target() failure: draw_image() returned 0.\n");
            }
            break;
        default:
            fsout(stdout, "show_render_target() failure: invalid render_target_type.\n");
    }
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
