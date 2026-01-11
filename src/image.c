
#include "image.h"

image* init_image(SDL_Renderer* r, const char* file)
{
    SDL_IOStream* src;
    SDL_Surface* srf;
    image* img;

    img = (image*) malloc(sizeof(struct image_data));
    img->file = (char*) file;
    
    if ((src = SDL_IOFromFile(img->file, "r")) == NULL)
    {
        fsout(stdout, "init_image() failure: %s\n", SDL_GetError());
    }
    if ((srf = IMG_LoadPNG_IO(src)) == NULL)
    {
        fsout(stdout, "init_image() failure: Unable to load png!\n");
    }
    if ((img->txr = SDL_CreateTextureFromSurface(r, srf)) == NULL)
    {
        fsout(stdout, "init_image() failure: %s\n", SDL_GetError());
    }

    SDL_DestroySurface(srf);
    SDL_CloseIO(src);

    return img;
}

bool draw_image(SDL_Renderer* r, SDL_FRect dst, image* img)
{
    bool success = true;

    if (!SDL_RenderTexture(r, img->txr, NULL, &dst))
    {
        fsout(stdout, "draw_image() failure: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}


void term_image(image* img)
{
    SDL_DestroyTexture(img->txr);
    free(img);
}
