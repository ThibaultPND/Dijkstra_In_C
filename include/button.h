#if !defined(__BUTTON_H__)
#define __BUTTON_H__

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Rect rect;

    SDL_Color color;

    void (*onClick)(void*);
} Button;

void initButton(Button *button, int x, int y, int w, int h, SDL_Color color, void (*onClick)(void *));
void drawButton(Button *boutons, int button_count);
int isPointInsideButton(Button *button, int x, int y);

#endif // __BUTTON_H__
