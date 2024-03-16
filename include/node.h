#if !defined(__NODE_H__)
#define __NODE_H__

typedef struct
{
    int gCost; // Current to start.
    int hCost; // Current to end.
    int fCost; // g + h costs.
} t_Costs;

typedef struct Node
{
    // To have an unique texture placement.
    SDL_Rect *texture;

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
void PrintNodeList(NodeList *node_list);
void AddNodeToList(NodeList **node_list, Node *node);
void RemoveNodeInList(NodeList **node_list, Node *nodeToRemove);
NodeList *SearchNodeInList(NodeList *node_list, SDL_Point position);

void ClearNodeList(NodeList **node_list);
#endif // __NODE_H__
