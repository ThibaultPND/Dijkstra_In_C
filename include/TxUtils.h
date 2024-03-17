#ifndef __TXUTILS_H__
#define __TXUTILS_H__

SDL_Texture *LoadTexture(const char *path);
SDL_Texture *LoadingTextureAndRect(const char *path, SDL_Rect *rect, Uint16 x, Uint16 y);
SDL_Rect getRectFromTexture(SDL_Texture *texture, int x, int y);
void thickLine(int x1, int y1, int x2, int y2, int thickness);

#endif // __TXUTILS__H_
