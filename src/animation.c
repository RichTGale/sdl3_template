

#include "animation.h"

struct {
    render_target* test_img;    // Background image
    render_target* test_txt;    // The text
    render_target* test_btn;    // A Button
    char* txt;
} example_animation;

animation* init_animation(enum AnimationTypes animation_type, SDL_Window* win, SDL_Renderer* r, TTF_TextEngine* te)
{
    SDL_FRect text_src;
    animation* ani = (animation*) malloc(sizeof(struct animation_data));
    int win_w, win_h;
    int num_chars;

    array_init(&(ani->render_targets));
    ani->animation_type = animation_type;

    switch (ani->animation_type)
    {
        case ANIMATION_TYPE_EXAMPLE:

            /* Print a status message. */
            fsout(stdout, "Creating the example animation.\n");

            /* Get the window size. */
            if (!SDL_GetWindowSizeInPixels(win, &win_w, &win_h))
            {
                fsout(stdout, "init_animations() failure: %s\n", SDL_GetError());
            }

            /* Create the background image. */
            example_animation.test_img = init_render_target_image(r, 0, "./img/test.jpg", 0, 0, win_w, win_h);

            /* Create the text. 
             * Position the text afterwards because it needs to be created before we can get its width and height. */
            example_animation.txt = "Click the mouse to exit";
            example_animation.test_txt  = init_render_target_text(te, 2, "./fonts/Inconsolata-Regular.ttf", example_animation.txt, 0, 0, 255, 255, 255, 100);

            /* Get the text's rectangle. */
            text_src = get_render_target_src(*(example_animation.test_txt));

            /* Position the text. */
            set_render_target_src(example_animation.test_txt, (win_w / 2) - ((int) text_src.w / 2), (win_h / 2) - ((int) text_src.h / 2));

            /* Create the button. */
            example_animation.test_btn = init_render_target_image(r, 1, "./img/button-not-pressed.jpg", 
                    (win_w / 2) - ((int) text_src.w / 2), (win_h / 2) - ((int) text_src.h / 2), (int) text_src.w, (int) text_src.h);

            /* Add the render targets to the array of render targets. */
            array_push_back(&(ani->render_targets), (void*) example_animation.test_img);
            array_push_back(&(ani->render_targets), (void*) example_animation.test_txt);
            array_push_back(&(ani->render_targets), (void*) example_animation.test_btn);

            break;
            
        case ANIMATION_TYPE_NONE:
            break;
    }

    return ani;
}

bool animation_clicked(animation ani, int x, int y)
{
    render_target* rt;
    bool clicked = false;

    switch (ani.animation_type)
    {
        case ANIMATION_TYPE_EXAMPLE:

		    for (int i = 0; i < array_size(ani.render_targets); i++)
		    {
		        rt = (render_target*) array_get_data(ani.render_targets, i);
		        if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
		            (y >= rt->src.y && y <= rt->src.y + rt->src.h))
		        {
                    if (rt == example_animation.test_btn)
                    {
		                clicked = true;
                    }
		        }
		    }
            break;
        
        case ANIMATION_TYPE_NONE:
            break;
    }

    return clicked;
}

array* get_render_targets(animation* ani)
{
    return &(ani->render_targets);
}

void term_animation(animation* ani)
{
    fsout(stdout, "Cleaning up the current animation.\n");

    switch (ani->animation_type)
    {
        case ANIMATION_TYPE_EXAMPLE:
            term_render_target(example_animation.test_img);
            term_render_target(example_animation.test_txt);
            term_render_target(example_animation.test_btn);
            break;
    }

    array_free(&(ani->render_targets));
    
    free(ani);
}

