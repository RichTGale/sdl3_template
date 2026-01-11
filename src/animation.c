

#include "animation.h"

struct {
    render_target* img_background;
    render_target* btn_exit;
    render_target* btn_exit_pressed;
    render_target* txt_exit;
    char* txt;
    bool exit;
} basics;

struct {
    render_target* img_disconnected;
    render_target* img_connected;
    render_target* txt_connected;
    render_target* txt_disconnected;
    char* txt;
    bool connected;
} midi;

animation* init_animation(enum AnimationTypes animation_type, SDL_Window* win, SDL_Renderer* r, TTF_TextEngine* te)
{
    SDL_FRect btn_rect;
    SDL_FRect txt_rect;
    animation* ani = (animation*) malloc(sizeof(struct animation_data));
    int win_w, win_h;
    int num_chars;
    int padding = 5;

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
            basics.txt_exit = init_render_target_text(te, 1, "./fonts/Inconsolata-Regular.ttf", "Exit", 0, 0, 255, 255, 255, 100);
            btn_rect = get_render_target_src(*(basics.btn_exit));
            txt_rect = get_render_target_src(*(basics.txt_exit));
            set_render_target_src(basics.txt_exit, (btn_rect.x + btn_rect.w / 2) - txt_rect.w / 2, (btn_rect.y + btn_rect.h / 2) - txt_rect.h / 2);
            array_push_back(&(ani->render_targets), (void*) basics.txt_exit);

            basics.exit = false;

            break;

        case ANIMATION_TYPE_MIDI:

            fsout(stdout, "Creating the Peak animation\n");
            
            /* Get the window size. */
            if (!SDL_GetWindowSizeInPixels(win, &win_w, &win_h))
            {
                fsout(stdout, "init_animations() failure: %s\n", SDL_GetError());
            }
            
            btn_rect = get_render_target_src(*(basics.btn_exit));
            
            /* Create the images. */
            midi.img_disconnected = init_render_target_image(r, 3, "./img/button_green_1.png", btn_rect.x, btn_rect.y + btn_rect.h + padding, btn_rect.w, btn_rect.h);
            midi.img_connected = init_render_target_image(r, 3, "./img/button_green_1_pressed.png", btn_rect.x, btn_rect.y + btn_rect.h + padding, btn_rect.w, btn_rect.h);
            
            
            midi.txt_disconnected  = init_render_target_text(te, 4, "./fonts/Inconsolata-Regular.ttf", "Peak --> Disconnected", 0, 0, 255, 255, 255, 100);
            btn_rect = get_render_target_src(*(midi.img_disconnected));
            txt_rect = get_render_target_src(*(midi.txt_disconnected));
            set_render_target_src(midi.txt_disconnected, (btn_rect.x + btn_rect.w / 2) - txt_rect.w / 2, (btn_rect.y + btn_rect.h / 2) - txt_rect.h / 2);
            
            midi.txt_connected  = init_render_target_text(te, 4, "./fonts/Inconsolata-Regular.ttf", "Peak --> Connected", 0, 0, 255, 255, 255, 100);
            btn_rect = get_render_target_src(*(midi.img_connected));
            txt_rect = get_render_target_src(*(midi.txt_connected));
            set_render_target_src(midi.txt_connected, (btn_rect.x + btn_rect.w / 2) - txt_rect.w / 2, (btn_rect.y + btn_rect.h / 2) - txt_rect.h / 2);

            /* Add the render targets to the animation render target array. */
            array_push_back(&(ani->render_targets), (void*) midi.img_disconnected);
            array_push_back(&(ani->render_targets), (void*) midi.txt_disconnected);

            midi.connected = false;
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
//                        basics.exit = true;
                        clicked = true;
                    }
                }
                break;
            case ANIMATION_TYPE_MIDI:
                if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
                    (y >= rt->src.y && y <= rt->src.y + rt->src.h))
                {
                    if (rt == midi.img_disconnected)
                    {
	                    midi.connected = true;
                    }
                    else if (rt == midi.img_connected)
                    {
                        midi.connected = false;
                    }
                }
            break;
        }
    }

    return clicked;
}

void animation_update(animation* ani)
{
    render_target* rt;

    for (int i = 0; i < array_size(ani->render_targets); i++)
    {
        rt = (render_target*) array_get_data(ani->render_targets, i);
        switch (ani->animation_type)
        {
	        case ANIMATION_TYPE_BASICS:

	            break;
            case ANIMATION_TYPE_MIDI:
                if (rt == midi.img_disconnected && midi.connected)
                {
                    array_set_data(&(ani->render_targets), i, midi.img_connected);
                    system("aconnect 'MPK mini 3':'MPK mini 3 MIDI 1' 'Peak':'Peak MIDI 1     ' > /dev/null 2>&1");
//                    system("aconnect 'MPK mini 3':'MPK mini 3 MIDI 1' 'Peak':'Peak MIDI 1     '");
                }
                if (rt == midi.img_connected && !midi.connected)
                {
                    array_set_data(&(ani->render_targets), i, midi.img_disconnected);
                    system("aconnect -d 'MPK mini 3':'MPK mini 3 MIDI 1' 'Peak':'Peak MIDI 1     ' > /dev/null 2>&1");
//                    system("aconnect -d 'MPK mini 3':'MPK mini 3 MIDI 1' 'Peak':'Peak MIDI 1     '");
                }
                if (rt == midi.txt_disconnected && midi.connected)
                {
                    array_set_data(&(ani->render_targets), i, midi.txt_connected);
                }
                if (rt == midi.txt_connected && !midi.connected)
                {
                    array_set_data(&(ani->render_targets), i, midi.txt_disconnected);
                }
                 break;
        }
    }
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
        case ANIMATION_TYPE_MIDI:
                if ((x >= rt->src.x && x <= rt->src.x + rt->src.w) &&
                    (y >= rt->src.y && y <= rt->src.y + rt->src.h))
                {
                    if (rt == midi.img_disconnected)
                    {
                        array_set_data(&(ani->render_targets), i, midi.img_connected);
                    }
                }
                else if (rt == midi.img_connected)
                {
                    if (midi.connected)
                    {
                        array_set_data(&(ani->render_targets), i, midi.img_disconnected);
                    }
                }
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
        case ANIMATION_TYPE_MIDI:
            term_render_target(midi.img_disconnected);
            term_render_target(midi.img_connected);
            term_render_target(midi.txt_disconnected);
            term_render_target(midi.txt_connected);
            break;
    }

    array_free(&(ani->render_targets));
    
    free(ani);
}

