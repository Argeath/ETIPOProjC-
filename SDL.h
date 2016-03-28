extern "C" {
	#include "./sdl/include/SDL.h"
	#include "./sdl/include/SDL_main.h"
}

#ifdef __cplusplus
extern "C"
#endif

#ifndef SDL_H
#define SDL_H

// narysowanie napisu txt na powierzchni screen, zaczynaj�c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj�ca znaki
void DrawString(int x, int y, const char *text);

SDL_Surface* LoadSurface(char* path);

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt �rodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface *sprite, int x, int y);

// rysowanie pojedynczego pixela
void DrawPixel(int x, int y, Uint32 color);


// rysowanie linii o d�ugo�ci l w pionie (gdy dx = 0, dy = 1) 
// b�d� poziomie (gdy dx = 1, dy = 0)
void DrawLine(int x, int y, int l, int dx, int dy, Uint32 color);


// rysowanie prostok�ta o d�ugo�ci bok�w l i k
void DrawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
#endif