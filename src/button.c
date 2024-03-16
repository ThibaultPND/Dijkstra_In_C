#include "Project.h"
#include "TxUtils.h"
#include "button.h"

// TODO Faire une fonction qui clear les boutons.

// Fonction pour initialiser un bouton
void initButton(Button *button, int x, int y, int w, int h, const char *path, void (*onClick)(void *))
{
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;
    button->texture = LoadTexture(path);
    button->onClick = onClick;
}

// Fonction pour dessiner un bouton
void drawButton(Button *button, int button_count)
{
    for (int i = 0; i < button_count; i++)
    {
        SDL_RenderCopy(renderer, button[i].texture, NULL, &button[i].rect);
    }
}

// Fonction pour vérifier si les coordonnées du clic de la souris se trouvent à l'intérieur d'un bouton
int isPointInsideButton(Button *button, int x, int y)
{
    return (x >= button->rect.x && x <= button->rect.x + button->rect.w &&
            y >= button->rect.y && y <= button->rect.y + button->rect.h);
}

void handleButtons(SDL_Point mouse, Button *boutons, int count_button)
{
    for (int i = 0; i < count_button; i++)
    {
        if (boutons[i].onClick != NULL && isPointInsideButton(&boutons[i], mouse.x, mouse.y))
        {
            boutons[i].onClick(NULL); // Appel de la fonction associée au clic avec les arguments
        }
    }
}