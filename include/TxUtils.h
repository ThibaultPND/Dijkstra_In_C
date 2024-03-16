#ifndef __TXUTILS_H__
#define __TXUTILS_H__

SDL_Texture *LoadTexture(const char *path);
SDL_Texture *LoadingTextureAndRect(const char *path, SDL_Rect *rect, Uint16 x, Uint16 y);
SDL_Rect getRectFromTexture(SDL_Texture *texture, int x, int y);

#endif // __TXUTILS__H_