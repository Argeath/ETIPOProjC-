#include "main.h"

using namespace Engine;

void DrawString(int x, int y, const char *text) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(Window::getActiveWindow()->getCharset(), &s, Window::getActiveWindow()->screen, &d);
		x += 8;
		text++;
	};
};

SDL_Surface* LoadSurface(char* text) {
	SDL_Surface* optimized = nullptr;

	SDL_Surface* loaded = SDL_LoadBMP(text);
	if (loaded == nullptr) {
		printf("Unable to load image %s! SDL Error: %s\n", text, SDL_GetError());
	}
	else {
		optimized = SDL_ConvertSurface(loaded, Engine::Window::getActiveWindow()->screen->format, NULL); 
		if (optimized == nullptr) { 
			printf("Unable to optimize image %s! SDL Error: %s\n", text, SDL_GetError()); 
		}
		SDL_FreeSurface( loaded );
	}
	return optimized;
}


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, nullptr, Window::getActiveWindow()->screen, &dest);
};


// rysowanie pojedynczego pixela
void DrawPixel(int x, int y, Uint32 color) {
	SDL_Surface* surface = Window::getActiveWindow()->screen;

	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
};


// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
void DrawLine(int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(x, y, color);
		x += dx;
		y += dy;
	};
};


// rysowanie prostokπta o d≥ugoúci bokÛw l i k
void DrawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	DrawLine(x, y, k, 0, 1, outlineColor);
	DrawLine(x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(x, y, l, 1, 0, outlineColor);
	DrawLine(x, y + k - 1, l, 1, 0, outlineColor);
	for (int i = y + 1; i < y + k - 1; i++)
		DrawLine(x + 1, i, l - 2, 1, 0, fillColor);
};