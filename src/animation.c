

#include "animation.h"

struct {
    render_target* img_background;
    render_target* btn_exit;
    render_target* btn_exit_pressed;
    render_target* txt_exit;
    char* txt;
} basics;

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

struct {
    render_target* col_disconnected;
    render_target* col_connected;
    render_target* col_hover;
    render_target* txt_connected;    // The text
    render_target* txt_disconnected;    // The text
    char* txt;
    bool connected;
} peak_animation;

animation* init_animation(enum AnimationTypes animation_type, SDL_Window* win, SDL_Renderer* r, TTF_TextEngine* te)
{
    SDL_FRect btn_rect;
    SDL_FRect txt_rect;
    SDL_FRect text_src;
    animation* ani = (animation*) malloc(sizeof(struct animation_data));
    int win_w, win_h;
    int num_chars;

    array_init(&(ani->render_targets));
    ani->animation_type = animation_type;

    switch (ani->animation_type)
    {
        case ANIMATION_TYPE_BASICS:
            
            /* Print a status message. */
            fsout(stdout, "Creating the basics animation.\n");

            /* Get the window size. */
            if (!SDL_GetWindowSizeInPixels(win, &win_w, &win_h))
            {
                fsout(stdout, "init_animations() failure: %s\n", SDL_GetError());
            }

            /* Create the background image. */
            basics.img_background = init_render_target_image(r, 0, "./img/background.png", 0, 0, win_w, win_h);
            array_push_back(&(ani->render_targets), (void*) basics.img_background);
            
            /* Create text image/button. */
            basics.btn_exit = init_render_target_image(r, 0, "./img/button_green_1.png", 5, 5, 150, win_h / 6);
            array_push_back(&(ani->render_targets), (void*) basics.btn_exit);
            basics.btn_exit_pressed = init_render_target_image(r, 0, "./img/button_green_1_pressed.png", 5, 5, 150, win_h / 6);
            array_push_back(&(ani->render_targets), (void*) basics.btn_exit_pressed);

            /* Create text. */
            basics.txt = "Exit";
            basics.txt_exit = init_render_target_text(te, 1, "./fonts/Inconsolata-Regular.ttf", basics.txt, 0, 0, 255, 255, 255, 100);
            btn_rect = get_render_target_src(*(basics.btn_exit));
            txt_rect = get_render_target_src(*(basics.txt_exit));
            set_render_target_src(basics.txt_exit, (btn_rect.x + btn_rect.w / 2) - txt_rect.w / 2, (btn_rect.y + btn_rect.h / 2) - txt_rect.h / 2);
            array_push_back(&(ani->render_targets), (void*) basics.txt_exit);


            break;
        
        case ANIMATION_TYPE_EXAMPLE:

            /* Print a status message. */
            fsout(stdout, "Creating the example animation.\n");

            /* Get the window size. */
            if (!SDL_GetWindowSizeInPixels(win, &win_w, &win_h))
            {
                fsout(stdout, "init_animations() failure: %s\n", SDL_GetError());
            }

            /* Create the background image. */
            example_animation.test_img = init_render_target_image(r, 0, "./img/background.png", 0, 0, win_w, win_h);

            /* Create the text. 
             * Position the text afterwards because it needs to be created before we can get its width and height. */
            example_animation.txt = "Double-click me!";
            example_animation.test_txt  = init_render_target_text(te, 2, "./fonts/Inconsolata-Regular.ttf", example_animation.txt, 0, 0, 255, 255, 255, 100);

            /* Get the text's rectangle. */
            text_src = get_render_target_src(*(example_animation.test_txt));

            /* Position the text. */
            set_render_target_src(example_animation.test_txt, (win_w / 2) - ((int) text_src.w / 2), (win_h / 2) - ((int) text_src.h / 2));

            /* Create the buttons. */
            example_animation.test_btn_01_not_pressed = init_render_target_image(r, 1, "./img/terafox-pallette/green_2.png", 
                    (win_w / 2) - ((int) text_src.w / 2), (win_h / 2) - ((int) text_src.h / 2), text_src.w, text_src.h);
            example_animation.test_btn_01_pressed = init_render_target_image(r, 1, "./img/terafox-pallette/green_3.png", 
                    (win_w / 2) - ((int) text_src.w / 2), (win_h / 2) - ((int) text_src.h / 2), text_src.w, text_src.h);
            example_animation.test_btn_02_not_hovered = init_render_target_image(r, 1, "./img/terafox-buttons/button_hover.png", 
                    0, 0, 100, 100);
            example_animation.test_btn_02_hovered = init_render_target_image(r, 1, "./img/terafox-buttons/button_pressed.png", 
                    0, 0, 100, 100);

            /* Add the render targets to the array of render targets. */
            array_push_back(&(ani->render_targets), (void*) example_animation.test_img);
            array_push_back(&(ani->render_targets), (void*) example_animation.test_txt);
            array_push_back(&(ani->render_targets), (void*) example_animation.test_btn_01_not_pressed);
            array_push_back(&(ani->render_targets), (void*) example_animation.test_btn_02_not_hovered);

            break;
        case ANIMATION_TYPE_FLASHER:
            
            /* Print a status message. */
            fsout(stdout, "Creating a flasher animation.\n");

            /* Get the window size. */
            if (!SDL_GetWindowSizeInPixels(win, &win_w, &win_h))
            {
                fsout(stdout, "init_animations() failure: %s\n", SDL_GetError());
            }

            flasher_animation.colour_01 = init_render_target_image(r, 1, "./img/terafox-pallette/green_0.png", win_w - 100, 0, 100, 100);
            flasher_animation.colour_02 = init_render_target_image(r, 1, "./img/terafox-pallette/green_1.png",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_03 = init_render_target_image(r, 1, "./img/terafox-pallette/green_2.png",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_04 = init_render_target_image(r, 1, "./img/terafox-pallette/green_3.png",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_05 = init_render_target_image(r, 1, "./img/terafox-pallette/red_0.png",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_06 = init_render_target_image(r, 1, "./img/terafox-pallette/red_1.png",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_07 = init_render_target_image(r, 1, "./img/terafox-pallette/red_2.png",  win_w - 100, 0, 100, 100);
            flasher_animation.colour_08 = init_render_target_image(r, 1, "./img/terafox-pallette/white_0.png", win_w - 100, 0, 100, 100); 

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

        case ANIMATION_TYPE_PEAK:

            fsout(stdout, "Creating the Peak animation\n");
            
            /* Get the window size. */
            if (!SDL_GetWindowSizeInPixels(win, &win_w, &win_h))
            {
                fsout(stdout, "init_animations() failure: %s\n", SDL_GetError());
            }
            
            /* Position the text afterwards because it needs to be created before we can get its width and height. */
            peak_animation.txt_disconnected  = init_render_target_text(te, 4, "./fonts/Inconsolata-Regular.ttf", "Peak --> Disconnected", 0, 0, 255, 255, 255, 100);
            peak_animation.txt_connected  = init_render_target_text(te, 4, "./fonts/Inconsolata-Regular.ttf", "Peak --> Connected", 0, 0, 255, 255, 255, 100);
            
            /* Position the text. */
            text_src = get_render_target_src(*(peak_animation.txt_connected));
            set_render_target_src(peak_animation.txt_connected, 0, 0);
            text_src = get_render_target_src(*(peak_animation.txt_disconnected));
            set_render_target_src(peak_animation.txt_disconnected, 0, 0);

            text_src = get_render_target_src(*(peak_animation.txt_disconnected));
            
            /* Create the images. */
            peak_animation.col_disconnected = init_render_target_image(r, 3, "./img/terafox-pallette/red_0.png", 
                    (int )text_src.x, (int) text_src.y, (int) text_src.w, (int) text_src.h);
            peak_animation.col_connected = init_render_target_image(r, 3, "./img/terafox-pallette/green_3.png", 
                    (int )text_src.x, (int) text_src.y, (int) text_src.w, (int) text_src.h);
            peak_animation.col_hover = init_render_target_image(r, 3, "./img/terafox-pallette/green_2.png", 
                    (int )text_src.x, (int) text_src.y, (int) text_src.w, (int) text_src.h);

            /* Add the render targets to the animation render target array. */
            array_push_back(&(ani->render_targets), (void*) peak_animation.txt_disconnected);
            array_push_back(&(ani->render_targets), (void*) peak_animation.col_disconnected);

            peak_animation.connected = false;
    }

    return ani;
}

bool animation_clicked(animation* ani, int x, int y)
{
    render_target* rt;
    bool clicked = false;

    for (int i = 0; i < array_size(ani->render_targets); i++)
    {
        rt = (render_target*) array_get_data(ani->render_targets, i);
        switch (ani->animation_type)
        {
            case ANIMATION_TYPE_BASICS:
                if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
                    (y >= rt->src.y && y <= rt->src.y + rt->src.h))
                {
                    if (rt == basics.btn_exit_pressed)
                    {
                        clicked = true;
                    }
                }
                break;
        case ANIMATION_TYPE_EXAMPLE:
//
//                rt = (render_target*) array_get_data(ani->render_targets, i);
//                if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
//                    (y >= rt->src.y && y <= rt->src.y + rt->src.h))
//                {
//                    if (rt == example_animation.test_btn_01_not_pressed)
//                    {
//                        array_set_data(&(ani->render_targets), i, example_animation.test_btn_01_pressed);
//                    }
//                    else if (rt == example_animation.test_btn_01_pressed)
//                    {
//                        array_set_data(&(ani->render_targets), i, example_animation.test_btn_01_not_pressed);
//                        clicked = true;
//                    }
//                }
            break;
        case ANIMATION_TYPE_FLASHER:
            break;
        case ANIMATION_TYPE_PEAK:
//                rt = (render_target*) array_get_data(ani->render_targets, i);
//                if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
//                    (y >= rt->src.y && y <= rt->src.y + rt->src.h))
//                {
//                    if (rt == peak_animation.col_disconnected)
//                    {
//                        array_set_data(&(ani->render_targets), i, peak_animation.col_connected);
//                        system("aconnect 'MPK mini 3':'MPK mini 3 MIDI 1' 'Peak':'Peak MIDI 1     ' > /dev/null 2>&1");
//	                    peak_animation.connected = true; // TODO: Assert that it is connected.
//                    }
//                    else if (rt == peak_animation.col_connected)
//                    {
//                        array_set_data(&(ani->render_targets), i, peak_animation.col_disconnected);
//                        system("aconnect -d 'MPK mini 3':'MPK mini 3 MIDI 1' 'Peak':'Peak MIDI 1     ' > /dev/null 2>&1");
//                        peak_animation.connected = false; // TODO: assert that it is disconnected.
//                    }
//                    if (rt == peak_animation.txt_connected)
//                    {
//                        array_set_data(&(ani->render_targets), i, peak_animation.txt_disconnected);
//                    }
//                    else if (rt == peak_animation.txt_disconnected)
//                    {
//                        array_set_data(&(ani->render_targets), i, peak_animation.txt_connected);
//                    }
//                }
            break;
        }
    }

    return clicked;
}

void animation_run(animation* ani)
{
//    render_target* rt;
//
//    switch (ani->animation_type)
//    {
//	    case ANIMATION_TYPE_EXAMPLE:
//	        break;
//	    case ANIMATION_TYPE_FLASHER:
//	    if (timer_nano_elapsed(*(flasher_animation.timer), NANOS_PER_SEC / 10))
//	    {
//	        for (int i = 0; i < array_size(ani->render_targets); i++)
//	        {
//	            rt = (render_target*) array_get_data(ani->render_targets, i);
//	            if (rt == (render_target*) array_get_data(flasher_animation.colours, flasher_animation.current_colour))
//	            {
//	                flasher_animation.current_colour++;
//	                if (flasher_animation.current_colour >= array_size(flasher_animation.colours))
//	                {
//	                    flasher_animation.current_colour = 0;
//	                }
//	                array_set_data(&(ani->render_targets), i, array_get_data(flasher_animation.colours, flasher_animation.current_colour));
//	            }
//	        }
//	        timer_nano_reinit(flasher_animation.timer);
//	    }
//	    break;
//        case ANIMATION_TYPE_PEAK:
//        break;
//    }
}

void animation_hovered(animation* ani, int x, int y)
{
    render_target* rt;

    for (int i = 0; i < array_size(ani->render_targets); i++)
    {
        rt = (render_target*) array_get_data(ani->render_targets, i);
        switch (ani->animation_type)
        {
            case ANIMATION_TYPE_BASICS:
                if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
                    (y >= rt->src.y && y <= rt->src.y + rt->src.h))
                {
                    if (rt == basics.btn_exit)
                    {
                        array_set_data(&(ani->render_targets), i, basics.btn_exit_pressed);
                    }
                }
                else if (rt == basics.btn_exit_pressed)
                {
                    array_set_data(&(ani->render_targets), i, basics.btn_exit);
                }

                break;
        case ANIMATION_TYPE_EXAMPLE:
//
//            for (int i = 0; i < array_size(ani->render_targets); i++)
//            {
//                rt = (render_target*) array_get_data(ani->render_targets, i);
//                if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
//                    (y >= rt->src.y && y <= rt->src.y + rt->src.h))
//                {
//                    if (rt == example_animation.test_btn_02_not_hovered)
//                    {
//                        array_set_data(&(ani->render_targets), i, example_animation.test_btn_02_hovered);
//                    }
//                }
//                else if (rt == example_animation.test_btn_02_hovered)
//                {
//                        array_set_data(&(ani->render_targets), i, example_animation.test_btn_02_not_hovered);
//                }
//            }
            break;
        case ANIMATION_TYPE_FLASHER:
            break;
        case ANIMATION_TYPE_PEAK:
//            for (int i = 0; i < array_size(ani->render_targets); i++)
//            {
//                rt = (render_target*) array_get_data(ani->render_targets, i);
//                if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
//                    (y >= rt->src.y && y <= rt->src.y + rt->src.h))
//                {
//                    if (rt == peak_animation.col_disconnected)
//                    {
////                        array_set_data(&(ani->render_targets), i, peak_animation.col_hover);
//                    }
//                }
//                else if (rt == peak_animation.col_hover)
//                {
//                    if (peak_animation.connected)
//                    {
////                        array_set_data(&(ani->render_targets), i, peak_animation.col_connected);
//                    }
//                    else
//                    {
////                        array_set_data(&(ani->render_targets), i, peak_animation.col_disconnected);
//                    }
//                }
            break;
        }
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
        case ANIMATION_TYPE_BASICS:
            term_render_target(basics.img_background);
            term_render_target(basics.txt_exit);
            term_render_target(basics.btn_exit);
            break;
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
        case ANIMATION_TYPE_PEAK:
            term_render_target(peak_animation.col_disconnected);
            term_render_target(peak_animation.col_connected);
            term_render_target(peak_animation.col_hover);
            term_render_target(peak_animation.txt_disconnected);
            term_render_target(peak_animation.txt_connected);
            break;
    }

    array_free(&(ani->render_targets));
    
    free(ani);
}

