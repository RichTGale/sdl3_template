

#include "page.h"

struct {
    SDL_FRect rect;
    render_target* test_img;
    render_target* test_txt;
    char* txt;
} example_page;

page* init_page(enum GuiPages gui_page, SDL_Renderer* r, TTF_TextEngine* te, int x, int y, int w, int h)
{

    page* p = (page*) malloc(sizeof(struct page_data));
    array_init(&(p->render_targets));

    switch (gui_page)
    {
        case EXAMPLE_PAGE:
            fsout(stdout, "Creating the example page.\n");
		    example_page.test_img = init_render_target_image(r, 0, "./img/test.jpg", 0, 0);
		    example_page.txt = "Click the mouse to exit";
		    example_page.test_txt  = init_render_target_text(te, 1, "./fonts/Hybrid_b.ttf", example_page.txt, 230, 200, 0, 0, 0, 100);
            example_page.rect.x = x; example_page.rect.x = y; example_page.rect.x = w; example_page.rect.x = h;
            array_push_back(&(p->render_targets), (void*) example_page.test_img);
            array_push_back(&(p->render_targets), (void*) example_page.test_txt);
            break;
    }

    return p;
}

array* get_render_targets(page* p)
{
    return &(p->render_targets);
}


void term_page(page* p)
{
    fsout(stdout, "Cleaning up the current page.\n");
    while (array_size(p->render_targets) < 0)
    {
        term_render_target(array_pop_back(&(p->render_targets)));
        term_render_target(array_pop_back(&(p->render_targets)));
    }
    array_free(&(p->render_targets));
    free(p);
}

