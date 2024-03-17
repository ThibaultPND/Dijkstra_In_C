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

#define DISTANCE_MAX_NODE_CREATION 100
#define DISTANCE_MAX_LINK_CREATION 20
#define DISTANCE_MAX_SUPPRESSION 10

extern SDL_Renderer *renderer;
extern SDL_Window *window;

extern Node *startNode;
extern Node *endNode;
typedef enum
{
    NODE,
    LINK,
    MOVE,
    START,
    END
} cursor_t;

void renderMap(NodeList *nodes);
void renderCursorMode(cursor_t);
void handleNodeClickAction(SDL_Point mouse, NodeList **nodes, cursor_t cursor_mode);
void ErrorBox(const char *message);
int FindShortestPath(NodeList *nodes, Node *start, Node *end);

#endif // __PROJECT_H__
