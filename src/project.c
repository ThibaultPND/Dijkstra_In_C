#include "Project.h"
#include "TxUtils.h"

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;

void renderMap(NodeList *nodes)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 255);
    SDL_Rect rect = {0, 0, LARGEUR_FENETRE - LARGEUR_GUI, 800};
    SDL_RenderFillRect(renderer, &rect);

    SDL_Texture *nodeTx = LoadTexture("assets/move.bmp");

    NodeList *current = nodes;
    int count = 0;
    while (current != NULL)
    {
        SDL_Rect current_node_rect = getRectFromTexture(nodeTx, nodes->node->position.x, nodes->node->position.y);
        SDL_RenderCopy(renderer, nodeTx, NULL, &current_node_rect);
        current = current->next;
        count++;
    }
}

void ErrorBox(const char *message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, NULL);
}