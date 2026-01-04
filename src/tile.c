

#include "tile.h"

tile* init_tile(SDL_Renderer* r, TTF_TextEngine* te, int x, int y, int w, int h)
{
    render_target* test_img;
    render_target* test_txt;
    char* txt;

    tile* t = (tile*) malloc(sizeof(struct tile_data));
    
    test_img = init_render_target_image(r, 0, "./img/test.jpg", 0, 0);
    txt = "Click the mouse to exit";
    test_txt  = init_render_target_text(te, 1, "./fonts/Hybrid_b.ttf", txt, 230, 200, 0, 0, 0, 100);

    t->rct.x = x; t->rct.x = y; t->rct.x = w; t->rct.x = h;
    array_init(&(t->render_targets));

    array_push_back(&(t->render_targets), (void*) test_img);
    array_push_back(&(t->render_targets), (void*) test_txt);

    return t;
}

array* get_render_targets(tile* t)
{
    return &(t->render_targets);
}


void term_tile(tile* t)
{
    while (array_size(t->render_targets) < 0)
    {
        term_render_target(array_pop_back(&(t->render_targets)));
        term_render_target(array_pop_back(&(t->render_targets)));
    }
    array_free(&(t->render_targets));
    free(t);
}

