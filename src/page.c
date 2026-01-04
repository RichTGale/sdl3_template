

#include "page.h"

struct {
//    SDL_FRect rect;
    render_target* test_img;
    render_target* test_txt;
    char* txt;
} example_page;

page* init_page(enum GuiPages gui_page, SDL_Window* win, SDL_Renderer* r, TTF_TextEngine* te)
{

    SDL_FRect text_src;
    page* p = (page*) malloc(sizeof(struct page_data));
    int win_w, win_h;
    int num_chars;
    

    array_init(&(p->render_targets));

    switch (gui_page)
    {
        case EXAMPLE_PAGE:

            /* Print a status message. */
            fsout(stdout, "Creating the example page.\n");
		   
            /* Get the window size. */
            if (!SDL_GetWindowSizeInPixels(win, &win_w, &win_h))
		    {
		        fsout(stdout, "init_pages() failure: %s\n", SDL_GetError());
		    }

            /* Create the background image. */
            example_page.test_img = init_render_target_image(r, 0, "./img/test.jpg", 0, 0, win_w, win_h);

            /* Create the text. */
		    example_page.txt = "Click the mouse to exit";
		    example_page.test_txt  = init_render_target_text(te, 1, "./fonts/Inconsolata-Regular.ttf", example_page.txt, 0, 0, 0, 0, 0, 100);

            /* Get the text's rect. */
            text_src = get_render_target_src(*(example_page.test_txt));

            /* Position the text. */
	        set_render_target_src(example_page.test_txt, (win_w / 2) - ((int) text_src.w / 2), (win_h / 2) - ((int) text_src.h / 2));

            /* Add the render targets to the array of render targets. */
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
//        term_render_target(array_pop_back(&(p->render_targets)));
    }
    array_free(&(p->render_targets));
    free(p);
}

