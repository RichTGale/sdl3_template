#include "text.h"

text* init_text(TTF_TextEngine* te, char* font_path, char* txt, int r, int g, int b, int a)
{
    text* t = (text*) malloc(sizeof(struct text_data));
    
    /* Open a font. */
    if ((t->f = TTF_OpenFont(font_path, 30)) == NULL)
    {
        fsout(stdout, "TTF font opening failure: %s\n", SDL_GetError());
    }

    /* Create some text. */
    if ((t->t = TTF_CreateText(te, t->f, txt, 0)) == NULL)
    {
        fsout(stdout, "TTf text creation failure: %s\n", SDL_GetError());
    }

	
    /* Cghange the text colour. */
    if (!TTF_SetTextColor(t->t, r, g, b, a))
    {
        fsout(stdout, "TTF text colur change failure: %s\n", SDL_GetError());
    }

    return t;
}

bool draw_text(text* t, SDL_FRect src)
{
    bool success;

    if (!(success = TTF_DrawRendererText(t->t, src.x, src.y)))
    {
        fsout(stdout, "draw_text() failure: %s\n", SDL_GetError());
    }

    return success;
}


void term_text(text* t)
{
    TTF_DestroyText(t->t);
    TTF_CloseFont(t->f);
}
