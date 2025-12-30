
#include "render_target.h"


render_target* init_render_target_text(TTF_TextEngine* te, int render_layer, char* font_path, char* _text)
{
    render_target* rt = (render_target*) malloc(sizeof(struct render_target_data));

    rt->render_target_type = RENDER_TARGET_TEXT;
    rt->render_layer = render_layer;
  
    rt->txt = init_text(te, font_path, _text, 255, 255, 255, 255);
    
    return rt;
}

render_target* init_render_target_image(SDL_Renderer* r, int render_layer, char* img_path)
{
    render_target* rt = (render_target*) malloc(sizeof(struct render_target_data));

    rt->render_target_type = RENDER_TARGET_IMAGE;
    rt->render_layer = render_layer;
  
    rt->img = init_image(r, img_path);

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
            if(!draw_text(rt->txt))
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
    if (rt->txt != NULL)
    {
        term_text(rt->txt);
    }
    if (rt->img != NULL)
    {
        term_image(rt->img);
    }

    free(rt);
}
