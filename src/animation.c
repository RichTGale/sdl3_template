

#include "animation.h"

struct {
    render_target* test_img;    // Background image
    render_target* test_txt;    // The text
    render_target* test_btn_01_not_pressed;
    render_target* test_btn_01_pressed;
    render_target* test_btn_02_not_hovered;
    render_target* test_btn_02_hovered;
    char* txt;
} example_animation;

struct {
    render_target* colour_01;
    render_target* colour_02;
    render_target* colour_03;
    render_target* colour_04;
    render_target* colour_05;
    render_target* colour_06;
    render_target* colour_07;
    render_target* colour_08;
    array colours;
    timer_nano* timer;
    int current_colour;
} flasher_animation;

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
            example_animation.test_img = init_render_target_image(r, 0, "./img/terafox-pallette/green_0.jpg", 0, 0, win_w, win_h);

            /* Create the text. 
             * Position the text afterwards because it needs to be created before we can get its width and height. */
            example_animation.txt = "Double-click me!";
            example_animation.test_txt  = init_render_target_text(te, 2, "./fonts/Inconsolata-Regular.ttf", example_animation.txt, 0, 0, 255, 255, 255, 100);

            /* Get the text's rectangle. */
            text_src = get_render_target_src(*(example_animation.test_txt));

            /* Position the text. */
            set_render_target_src(example_animation.test_txt, (win_w / 2) - ((int) text_src.w / 2), (win_h / 2) - ((int) text_src.h / 2));

            /* Create the buttons. */
            example_animation.test_btn_01_not_pressed = init_render_target_image(r, 1, "./img/terafox-pallette/green_2.jpg", 
                    (win_w / 2) - ((int) text_src.w / 2), (win_h / 2) - ((int) text_src.h / 2), text_src.w, text_src.h);
            example_animation.test_btn_01_pressed = init_render_target_image(r, 1, "./img/terafox-pallette/green_3.jpg", 
                    (win_w / 2) - ((int) text_src.w / 2), (win_h / 2) - ((int) text_src.h / 2), text_src.w, text_src.h);
            example_animation.test_btn_02_not_hovered = init_render_target_image(r, 1, "./img/terafox-buttons/button_hover.jpg", 
                    0, 0, 100, 100);
            example_animation.test_btn_02_hovered = init_render_target_image(r, 1, "./img/terafox-buttons/button_pressed.jpg", 
                    0, 0, 100, 100);

            /* Add the render targets to the array of render targets. */
            array_push_back(&(ani->render_targets), (void*) example_animation.test_img);
            array_push_back(&(ani->render_targets), (void*) example_animation.test_txt);
            array_push_back(&(ani->render_targets), (void*) example_animation.test_btn_01_not_pressed);
            array_push_back(&(ani->render_targets), (void*) example_animation.test_btn_02_not_hovered);

            break;
        case ANIMATION_TYPE_FLASHER:
            
            /* Print a status message. */
            fsout(stdout, "Creating the flasher animation.\n");

            /* Get the window size. */
            if (!SDL_GetWindowSizeInPixels(win, &win_w, &win_h))
            {
                fsout(stdout, "init_animations() failure: %s\n", SDL_GetError());
            }

            flasher_animation.colour_01 = init_render_target_image(r, 1, "./img/terafox-pallette/green_0.jpg", win_w - 100, 0, 100, 100);
            flasher_animation.colour_02 = init_render_target_image(r, 1, "./img/terafox-pallette/green_1.jpg",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_03 = init_render_target_image(r, 1, "./img/terafox-pallette/green_2.jpg",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_04 = init_render_target_image(r, 1, "./img/terafox-pallette/green_3.jpg",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_05 = init_render_target_image(r, 1, "./img/terafox-pallette/red_0.jpg",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_06 = init_render_target_image(r, 1, "./img/terafox-pallette/red_1.jpg",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_07 = init_render_target_image(r, 1, "./img/terafox-pallette/red_2.jpg",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_08 = init_render_target_image(r, 1, "./img/terafox-pallette/white_0.jpg", win_w - 100, 0, 100, 100); 

            array_push_back(&(ani->render_targets), (void*) flasher_animation.colour_01);
            flasher_animation.current_colour = 0;
            
            flasher_animation.timer = timer_nano_init();

            array_init(&(flasher_animation.colours));
            array_push_back(&(flasher_animation.colours), (void*) flasher_animation.colour_01);
            array_push_back(&(flasher_animation.colours), (void*) flasher_animation.colour_02);
            array_push_back(&(flasher_animation.colours), (void*) flasher_animation.colour_03);
            array_push_back(&(flasher_animation.colours), (void*) flasher_animation.colour_04);
            array_push_back(&(flasher_animation.colours), (void*) flasher_animation.colour_05);
            array_push_back(&(flasher_animation.colours), (void*) flasher_animation.colour_06);
            array_push_back(&(flasher_animation.colours), (void*) flasher_animation.colour_07);
            array_push_back(&(flasher_animation.colours), (void*) flasher_animation.colour_08);

            break;
    }

    return ani;
}

bool animation_clicked(animation* ani, int x, int y)
{
    render_target* rt;
    bool clicked = false;

    switch (ani->animation_type)
    {
        case ANIMATION_TYPE_EXAMPLE:

            for (int i = 0; i < array_size(ani->render_targets); i++)
            {
                rt = (render_target*) array_get_data(ani->render_targets, i);
                if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
                    (y >= rt->src.y && y <= rt->src.y + rt->src.h))
                {
                    if (rt == example_animation.test_btn_01_not_pressed)
                    {
                        array_set_data(&(ani->render_targets), i, example_animation.test_btn_01_pressed);
                    }
                    else if (rt == example_animation.test_btn_01_pressed)
                    {
                        array_set_data(&(ani->render_targets), i, example_animation.test_btn_01_not_pressed);
                        clicked = true;
                    }
                }
            }
            break;
        case ANIMATION_TYPE_FLASHER:
            break;
    }

    return clicked;
}

void animation_run(animation* ani)
{
    render_target* rt;

    switch (ani->animation_type)
    {
	    case ANIMATION_TYPE_EXAMPLE:
	        break;
	    case ANIMATION_TYPE_FLASHER:
	    if (timer_nano_elapsed(*(flasher_animation.timer), NANOS_PER_SEC / 10))
	    {
	        for (int i = 0; i < array_size(ani->render_targets); i++)
	        {
	            rt = (render_target*) array_get_data(ani->render_targets, i);
	            if (rt == (render_target*) array_get_data(flasher_animation.colours, flasher_animation.current_colour))
	            {
	                flasher_animation.current_colour++;
	                if (flasher_animation.current_colour >= array_size(flasher_animation.colours))
	                {
	                    flasher_animation.current_colour = 0;
	                }
	                array_set_data(&(ani->render_targets), i, array_get_data(flasher_animation.colours, flasher_animation.current_colour));
	            }
	        }
	        timer_nano_reinit(flasher_animation.timer);
	    }
	    break;
    }
}

void animation_hovered(animation* ani, int x, int y)
{
    render_target* rt;

    switch (ani->animation_type)
    {
        case ANIMATION_TYPE_EXAMPLE:

            for (int i = 0; i < array_size(ani->render_targets); i++)
            {
                rt = (render_target*) array_get_data(ani->render_targets, i);
                if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
                    (y >= rt->src.y && y <= rt->src.y + rt->src.h))
                {
                    if (rt == example_animation.test_btn_02_not_hovered)
                    {
                        array_set_data(&(ani->render_targets), i, example_animation.test_btn_02_hovered);
                    }
                }
                else if (rt == example_animation.test_btn_02_hovered)
                {
                        array_set_data(&(ani->render_targets), i, example_animation.test_btn_02_not_hovered);
                }
            }
            break;
        case ANIMATION_TYPE_FLASHER:
            break;
    }
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
            term_render_target(example_animation.test_btn_01_not_pressed);
            term_render_target(example_animation.test_btn_01_pressed);
            term_render_target(example_animation.test_btn_02_not_hovered);
            term_render_target(example_animation.test_btn_02_hovered);
            break;
        case ANIMATION_TYPE_FLASHER:
            term_render_target(flasher_animation.colour_01);
            term_render_target(flasher_animation.colour_02);
            term_render_target(flasher_animation.colour_03);
            term_render_target(flasher_animation.colour_04);
            term_render_target(flasher_animation.colour_05);
            term_render_target(flasher_animation.colour_06);
            term_render_target(flasher_animation.colour_07);
            term_render_target(flasher_animation.colour_08);
            array_free(&(flasher_animation.colours));
            timer_nano_term(flasher_animation.timer);
            break;
    }

    array_free(&(ani->render_targets));
    
    free(ani);
}

