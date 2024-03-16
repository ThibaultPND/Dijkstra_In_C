#ifndef __PROJECT_H__
#define __PROJECT_H__

// Inclusions
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "node.h"

// Macro dimensions fenêtre
#define LARGEUR_GUI 250
#define HAUTEUR_FENETRE 800
#define LARGEUR_FENETRE 750 + LARGEUR_GUI
#define GRID_SIZE 8
#define TILE_SIZE 100

extern SDL_Renderer *renderer;
extern SDL_Window *window;

typedef enum
{
    NODE,
    LINK,
    MOVE
} cursor_t;

void renderMap(NodeList *nodes);
void ErrorBox(const char *message);

#endif // __PROJECT_H__