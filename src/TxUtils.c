#include "Project.h"
#include "TxUtils.h"

SDL_Texture *LoadTexture(const char *path)
{
    SDL_Surface *imageSurface = NULL;
    SDL_Texture *imageTexture = NULL;

    imageSurface = SDL_LoadBMP(path);
    if (imageSurface == NULL)
    {
        // Surface error.
    }
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (imageTexture == NULL)
    {
        // Texture error.
    }
    SDL_FreeSurface(imageSurface);

    return imageTexture;
}

SDL_Texture *LoadingTextureAndRect(const char *path, SDL_Rect *rect, Uint16 x, Uint16 y)
{
    SDL_Surface *imageSurface = NULL;
    SDL_Texture *imageTexture = NULL;

    imageSurface = SDL_LoadBMP(path);
    if (imageSurface == NULL)
    {
        // ERROR
    }
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (imageTexture == NULL)
    {
        // ERROR
    }

    rect->x = x - (imageSurface->w / 2);
    rect->y = y - (imageSurface->h / 2);
    rect->w = imageSurface->w;
    rect->h = imageSurface->h;

    SDL_FreeSurface(imageSurface);
    return imageTexture;
}

SDL_Rect getRectFromTexture(SDL_Texture *texture, int x, int y) {
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    return (SDL_Rect){x - texW / 2, y - texH / 2, texW, texH};
}