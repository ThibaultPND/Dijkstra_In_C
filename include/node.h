#if !defined(__NODE_H__)
#define __NODE_H__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int gCost; // Current to start.
    int hCost; // Current to end.
    int fCost; // g + h costs.
} t_Costs;

typedef struct Node
{
    t_Costs costs;
    SDL_Point position;

    struct NodeList *neighbours;

    struct Node *parent;
} Node;

typedef struct NodeList
{
    Node *node;

    struct NodeList *next;
} NodeList;

NodeList *CreateNodeList();
int getDistance(SDL_Point start, SDL_Point end);
void PrintNodeList(NodeList *nodes);
void AddNodeToList(NodeList **nodes, Node *node);
void RemoveNodeInList(NodeList **nodes, Node *nodeToRemove);
SDL_bool IsNodeInList(NodeList *nodes, Node *node);
NodeList *GetClosestNodeInListByDistance(NodeList *nodes, SDL_Point caller_position, int dist);
void RemoveNeighbour(Node *node, Node *neighbour);
void ClearNodeList(NodeList **nodes);

#endif // __NODE_H__
