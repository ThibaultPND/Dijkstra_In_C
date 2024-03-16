/***************************************************************
**  Auteur : Thibault Chassagne
**  MAJ : 15/03/2024
*
**  Nom : Unadvanced GPS
*
*?  Description : Ce logiciel à pour but de crée un simulateur de GPS
*
gcc -o build\prog -Iinclude -Iinclude/SDL2 src/*.c -Llib -lSDL2main -lSDL2 -static -DSDL_MAIN_HANDLED && build\monProgramme.exe
***************************************************************/
#include <Project.h>
#include <SDL2/SDL.h>
#include "TxUtils.h"
#include "node.h"
#include "button.h"

void handleButtons(SDL_Point mouse, Button *boutons, int count_button);
void function(void *args)
{
    int *value = (int *)args;
    printf("Hello : %d !", *value);
}

int main(int argc, char *argv[])
{
    printf("Debut du programme...\n\n");

    // Initialisation
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        // Erreur init SDL.
    }

    window = SDL_CreateWindow("GPS 6D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, 0);
    if (window == NULL)
    {
        SDL_Quit();
        // Erreur lors de la création de la fenêtre.
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        // Erreur création du rendu
    }
    srand(SDL_GetTicks());
    SDL_Point mouse;

    // Creation des  boutons
    int button_count = 1;
    Button boutons[20];
    initButton(&boutons[0], 794, 215, 150, 57, (SDL_Color){255, 0, 0, 255}, &function);

    // Initialisation des noeuds
    NodeList *nodes = CreateNodeList();

    // Mode de la souris
    cursor_t cursor_mode = NODE;

    // Programme
    SDL_bool programLaunched = SDL_TRUE;
    while (programLaunched)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                programLaunched = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouse.x, &mouse.y);
                if (mouse.x >= LARGEUR_FENETRE - LARGEUR_GUI - 10) // 10 = Epsilon
                {
                    handleButtons(mouse, boutons, button_count);
                }
                else
                {
                    switch (cursor_mode)
                    {
                    case NODE:
                        NodeList *newNode = (NodeList *)malloc(sizeof(NodeList));
                        if (newNode != NULL)
                        {
                            newNode->node = (Node *)malloc(sizeof(Node)); // Allouer de la mémoire pour newNode->node
                            if (newNode->node != NULL)
                            {
                                newNode->next = nodes;
                                newNode->node->position.x = mouse.x;
                                newNode->node->position.y = mouse.y;
                                nodes = newNode;
                            }
                            else
                            {
                                free(newNode); // Libérer la mémoire allouée pour newNode
                                exit(1);
                            }
                        }
                        break;
                    case LINK:
                        /* code */
                        break;
                    case MOVE:
                        /* code */
                        break;

                    default:
                        break;
                    }
                }
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                    // Verifie les conditions de recherche.
                    if (SDL_FALSE)
                    {
                        ErrorBox("Les points de départ et d'arrivé ne sont pas tous défini. \nVeuillez utiliser les boutons de la souris pour les mettre en place");
                        break;
                    }
                    // Lancement de la recherche.
                    break;
                case SDLK_BACKSPACE:
                    system("cls");
                    printf("cleared\n");
                }
                break;
            default:
                break;
            }
        }

        // Boucle de rendu.
        SDL_SetRenderDrawColor(renderer, 0xF0, 0xF0, 0xF0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        renderMap(nodes);
        drawButton(boutons, button_count);
        SDL_RenderPresent(renderer);

        // Limitation du tps du programme à 60.
        SDL_Delay(16);
    }

    // Libération des ressources
    NodeList *current = nodes;
    NodeList *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        free(current->node);
        free(current);
        current = next;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("...fin du programme\n");

    return EXIT_SUCCESS;
}

void handleButtons(SDL_Point mouse, Button *boutons, int count_button)
{
    for (int i = 0; i < count_button; i++)
    {
        if (boutons[i].onClick != NULL && isPointInsideButton(&boutons[i], mouse.x, mouse.y))
        {
            int data = 4;
            boutons[i].onClick(&data); // Appel de la fonction associée au clic avec les arguments
        }
    }
}