#include "Project.h"
#include "TxUtils.h"
#include "button.h"

/** \todo Faire une fonction qui clear les boutons. */


cursor_t cursor_mode;
SDL_bool launch_search = SDL_FALSE;

void cursorToNode(void *args)
{
    cursor_mode = NODE;
}
void cursorToMove(void *args)
{
    cursor_mode = MOVE;
}
void cursorToLink(void *args)
{
    cursor_mode = LINK;
}
void buttonStart(void *args)
{
    cursor_mode = START;
}
void buttonEnd(void *args)
{
    cursor_mode = END;
}
void buttonLaunch(void *args)
{
    launch_search = SDL_TRUE;
}

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
