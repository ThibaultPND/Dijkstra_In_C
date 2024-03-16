#include "Project.h"
#include "button.h"

// Fonction pour initialiser un bouton
void initButton(Button *button, int x, int y, int w, int h, SDL_Color color, void (*onClick)(void *))
{
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;
    button->color = color;
    button->onClick = onClick;
}

// Fonction pour dessiner un bouton
void drawButton(Button *button, int button_count)
{
    for (int i = 0; i < button_count; i++)
    {
        SDL_SetRenderDrawColor(renderer, button[i].color.r, button[i].color.g, button[i].color.b, button[i].color.a);
        SDL_RenderFillRect(renderer, &button[i].rect);
    }
}

// Fonction pour vérifier si les coordonnées du clic de la souris se trouvent à l'intérieur d'un bouton
int isPointInsideButton(Button *button, int x, int y)
{
    return (x >= button->rect.x && x <= button->rect.x + button->rect.w &&
            y >= button->rect.y && y <= button->rect.y + button->rect.h);
}