#if !defined(__BUTTON_H__)
#define __BUTTON_H__

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Rect rect;

    SDL_Texture *texture;

    void (*onClick)(void *);
} Button;

extern cursor_t cursor_mode;
extern SDL_bool launch_search;

void initButton(Button *button, int x, int y, int w, int h, const char *path, void (*onClick)(void *));
void drawButton(Button *boutons, int button_count);
int isPointInsideButton(Button *button, int x, int y);
void handleButtons(SDL_Point mouse, Button *boutons, int count_button);

// callback
void cursorToNode(void *args);
void cursorToMove(void *args);
void cursorToLink(void *args);
void buttonStart(void *args);
void buttonEnd(void *args);
void buttonLaunch(void *args);

#endif // __BUTTON_H__
