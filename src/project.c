#include "Project.h"
#include "TxUtils.h"

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;

Node *selectedNode = NULL;

Node *startNode = NULL;
Node *endNode = NULL;

void renderMap(NodeList *nodes)
{
    // Nettoyer la map
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 255);
    SDL_Rect rect = {0, 0, LARGEUR_FENETRE - LARGEUR_GUI, 800};
    SDL_RenderFillRect(renderer, &rect);

    // Afficher les liens
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
    NodeList *current_node = nodes;
    while (current_node != NULL)
    {
        NodeList *current_neighbour = current_node->node->neighbours;
        while (current_neighbour != NULL)
        {
            thickLine(
                current_node->node->position.x,
                current_node->node->position.y,
                current_neighbour->node->position.x,
                current_neighbour->node->position.y,
                5);

            current_neighbour = current_neighbour->next;
        }

        current_node = current_node->next;
    }

    // Afficher les noeuds
    SDL_Texture *nodeTx = LoadTexture("assets/node.bmp");
    current_node = nodes;
    while (current_node != NULL)
    {
        SDL_Rect current_node_rect = getRectFromTexture(nodeTx, current_node->node->position.x, current_node->node->position.y);
        SDL_RenderCopy(renderer, nodeTx, NULL, &current_node_rect);
        current_node = current_node->next;
    }
    SDL_DestroyTexture(nodeTx);

    // Afficher le drapeau de départ.
    if (startNode != NULL)
    {
        SDL_Rect green_flag_rect;
        SDL_Texture *green_flag_texture = LoadingTextureAndRect("assets/green_flag.bmp", &green_flag_rect, startNode->position.x, startNode->position.y);
        green_flag_rect.y -= green_flag_rect.h / 2;
        green_flag_rect.x -= 9;
        SDL_RenderCopy(renderer, green_flag_texture, NULL, &green_flag_rect);
        SDL_DestroyTexture(green_flag_texture);
    }
    // Afficher le drapeau d'arrivée.
    if (endNode != NULL)
    {
        SDL_Rect red_flag_rect;
        SDL_Texture *red_flag_texture = LoadingTextureAndRect("assets/red_flag.bmp", &red_flag_rect, endNode->position.x, endNode->position.y);
        red_flag_rect.y -= red_flag_rect.h / 2;
        red_flag_rect.x += 9;
        SDL_RenderCopy(renderer, red_flag_texture, NULL, &red_flag_rect);
        SDL_DestroyTexture(red_flag_texture);
    }

    // Afficher le chemin le plus court si il y en a un.
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x80, 0x00, 255);
    Node *current = endNode;
    if (current != NULL)
        while (current->parent != NULL)
        {
            thickLine(
                current->position.x,
                current->position.y,
                current->parent->position.x,
                current->parent->position.y,
                5);

            current = current->parent;
        }
}
void renderCursorMode(cursor_t cursor)
{
    SDL_Texture *texture = NULL;
    switch (cursor)
    {
    case NODE:
        texture = LoadTexture("assets/cursor_node.bmp");
        break;
    case LINK:
        texture = LoadTexture("assets/cursor_link.bmp");
        break;
    case MOVE:
        texture = LoadTexture("assets/cursor_move.bmp");
        break;
    case START:
        texture = LoadTexture("assets/cursor_start.bmp");
        break;
    case END:
        texture = LoadTexture("assets/cursor_end.bmp");
        break;
    default:
        return;
    }
    SDL_Rect rect = {
        .x = 807,
        .y = 94,
        .w = 97,
        .h = 60};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

void handleNodeClickAction(SDL_Point mouse, NodeList **nodes, cursor_t cursor_mode)
{
    switch (cursor_mode)
    {
    case NODE:
        // Réinitialiser la variable selectedNode si le mode de curseur change
        selectedNode = NULL;

        // Supprimer le nœud le plus proche si le clic est sur un nœud existant
        NodeList *closestNode = GetClosestNodeInListByDistance(*nodes, mouse, DISTANCE_MAX_SUPPRESSION);
        if (closestNode != NULL)
        {
            if (closestNode->node == startNode)
            {
                startNode = NULL;
            }
            else if (closestNode->node == endNode)
            {
                endNode = NULL;
            }

            // Supprimer closest de la liste des voisins des voisins
            NodeList *neighbourNode = closestNode->node->neighbours;
            while (neighbourNode != NULL)
            {
                RemoveNodeInList(&neighbourNode->node->neighbours, closestNode->node);

                neighbourNode = neighbourNode->next;
            }
            ClearNodeList(&closestNode->node->neighbours);
            closestNode->node->parent = NULL;
            RemoveNodeInList(nodes, closestNode->node);
            break;
        }
        // Vérifier si le clic de souris est suffisamment éloigné des autres nœuds
        if (GetClosestNodeInListByDistance(*nodes, mouse, DISTANCE_MAX_NODE_CREATION) == NULL)
        {
            // Créer un nouveau nœud
            NodeList *newNode = (NodeList *)malloc(sizeof(NodeList));
            if (newNode != NULL)
            {
                newNode->node = (Node *)malloc(sizeof(Node)); // Allouer de la mémoire pour newNode->node
                if (newNode->node != NULL)
                {
                    newNode->next = *nodes;
                    newNode->node->position.x = mouse.x;
                    newNode->node->position.y = mouse.y;
                    newNode->node->neighbours = NULL;
                    newNode->node->parent = NULL;
                    *nodes = newNode;
                }
                else
                {
                    free(newNode); // Libérer la mémoire allouée pour newNode
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            // Le clic est trop proche d'un autre nœud, ne rien faire
        }
        break;
    case LINK:
        // Vérifier si le clic de souris est effectué sur un nœud existant
        NodeList *clickedNode = GetClosestNodeInListByDistance(*nodes, mouse, DISTANCE_MAX_LINK_CREATION);
        if (clickedNode != NULL)
        {
            // Si aucun nœud n'est déjà sélectionné, enregistrer le nœud cliqué comme premier nœud sélectionné
            if (selectedNode == NULL)
            {
                selectedNode = clickedNode->node;
            }
            else
            {
                // SearchNodeInListSi un premier nœud est déjà sélectionné, enregistrer le nœud cliqué comme second nœud sélectionné
                // Mettre à jour les listes de voisins des deux nœuds pour créer le lien entre eux
                if (selectedNode != clickedNode->node)
                {
                    // Si le lien existe déja. Le supprimer
                    if (IsNodeInList(selectedNode->neighbours, clickedNode->node) == SDL_FALSE)
                    {
                        AddNodeToList(&selectedNode->neighbours, clickedNode->node);
                        AddNodeToList(&clickedNode->node->neighbours, selectedNode);
                    }
                    else
                    {
                        RemoveNodeInList(&selectedNode->neighbours, clickedNode->node);
                        RemoveNodeInList(&clickedNode->node->neighbours, selectedNode);
                    }
                }
                // Réinitialiser la variable selectedNode pour la prochaine création de lien
                selectedNode = NULL;
            }
        }
        break;
    case START:
        clickedNode = GetClosestNodeInListByDistance(*nodes, mouse, DISTANCE_MAX_LINK_CREATION);
        if (clickedNode != NULL)
        {
            startNode = clickedNode->node;
        }

        break;
    case END:
        clickedNode = GetClosestNodeInListByDistance(*nodes, mouse, DISTANCE_MAX_LINK_CREATION);
        if (clickedNode != NULL)
        {
            endNode = clickedNode->node;
        }
        break;
    default:
        break;
    }
}

t_Costs GetCosts(Node *current, Node *parent, Node *endNode)
{
    t_Costs costs;
    if (parent != NULL)
    {
        costs.gCost = parent->costs.gCost + getDistance(current->position, parent->position);
    }
    else
    {
        costs.gCost = 0;
    }
    costs.hCost = getDistance(current->position, endNode->position);
    costs.fCost = costs.gCost + costs.hCost;

    return costs;
}

Node *findLowestFcostInList(NodeList *nodes)
{
    NodeList *current = nodes;
    Node *lowest = nodes->node;
    while (current != NULL)
    {
        if (current->node->costs.fCost < lowest->costs.fCost)
            lowest = current->node;

        current = current->next;
    }
    return lowest;
}

int FindShortestPath(Node *start, Node *end)
{
    if (start == NULL || end == NULL)
    {
        return 1;
    }

    NodeList *open = CreateNodeList();
    NodeList *close = CreateNodeList();

    AddNodeToList(&open, start);

    open->node->costs = GetCosts(open->node, NULL, end);

    while (open != NULL)
    {
        Node *current_node = findLowestFcostInList(open);

        RemoveNodeInList(&open, current_node);
        AddNodeToList(&close, current_node);

        if (current_node == end)
        {
            ClearNodeList(&open);
            ClearNodeList(&close);
            return 1;
        }
        
        NodeList *current_neighbour = current_node->neighbours;
        while (current_neighbour != NULL)
        {
            if (IsNodeInList(close, current_neighbour->node))
            {
                current_neighbour = current_neighbour->next;
                continue;
            }

            if (IsNodeInList(open, current_neighbour->node))
            {
                t_Costs new_costs = GetCosts(current_neighbour->node, current_node, end);
                if (new_costs.fCost < current_neighbour->node->costs.fCost)
                {
                    current_neighbour->node->costs.fCost = new_costs.fCost;
                    current_neighbour->node->parent = current_node;
                }
            }
            else
            {
                current_neighbour->node->costs = GetCosts(current_neighbour->node, current_node, end);
                current_neighbour->node->parent = current_node;
                AddNodeToList(&open, current_neighbour->node);
            }
            current_neighbour = current_neighbour->next;
        }
    }
    end->parent = NULL;
    return 0;
}

void ErrorBox(const char *message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, NULL);
}
