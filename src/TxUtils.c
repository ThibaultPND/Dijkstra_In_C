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

SDL_Rect getRectFromTexture(SDL_Texture *texture, int x, int y)
{
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    return (SDL_Rect){x - texW / 2, y - texH / 2, texW, texH};
}

void thickLine(int x1, int y1, int x2, int y2, int thickness)
{
    // Calculer les distances horizontale et verticale
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    // Déterminer le pas dans chaque direction
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    // Calculer l'erreur de déplacement
    int err = dx - dy;

    // Boucle de dessin
    while (x1 != x2 || y1 != y2)
    {
        // Dessiner une ligne de la largeur spécifiée
        for (int i = -thickness / 2; i <= thickness / 2; i++)
        {
            SDL_RenderDrawLine(renderer, x1 + i, y1, x2 + i, y2);
        }

        // Calculer la prochaine position
        int err2 = 2 * err;
        if (err2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}
