#include "Project.h"
#include "node.h"

// Prototype

// Function
NodeList *CreateNodeList()
{
    return NULL;
}

void PrintNodeList(NodeList *node_list)
{
    puts("====| List |=====");
    NodeList *current = node_list;
    while (current != NULL)
    {
        printf("[%d:%d] => ", current->node->position.x, current->node->position.y);
        current = current->next;
    }
    puts("NULL");
    puts("================");
}

void AddNodeToList(NodeList **node_list, Node *node)
{
    NodeList *newNode = (NodeList *)malloc(sizeof(NodeList));
    if (newNode == NULL)
    {
        fprintf(stderr, "Erreur d'allocation !\n");
        exit(EXIT_FAILURE);
    }
    newNode->node = node;
    newNode->next = *node_list;

    *node_list = newNode;
}

void RemoveNodeInList(NodeList **node_list, Node *nodeToRemove)
{
    if (*node_list == NULL || nodeToRemove == NULL)
    {
        return;
    }

    NodeList *current = *node_list;
    NodeList *prev = NULL;

    while (current != NULL)
    {
        if (current->node == nodeToRemove)
        {
            if (prev == NULL)
            {
                *node_list = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

void ClearNodeList(NodeList **node_list)
{
    NodeList *current = *node_list;
    NodeList *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *node_list = NULL;
}

int getDistance(SDL_Point start, SDL_Point end)
{
    return SDL_sqrt(SDL_pow(start.x - end.x, 2) + SDL_pow(start.y - end.y, 2));
}

NodeList *SearchNodeInList(NodeList *node_list, SDL_Point position)
{
    NodeList *current = node_list;
    while (current != NULL)
    {
        if (current->node->position.x == position.x &&
            current->node->position.y == position.y)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}