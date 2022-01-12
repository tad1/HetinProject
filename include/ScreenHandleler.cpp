#include "ScreenHandleler.h"
#include <stdio.h>

SDL_Renderer* ScreenHandleler::IGetRenderer()
{
	return renderer;
}

bool ScreenHandleler::IInitialize(const char* windowName, Vector2T<int> size)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL_Init falied: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	return true;
}

void ScreenHandleler::ISetBackgroundColor(SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void ScreenHandleler::IRender()
{
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

ScreenHandleler::~ScreenHandleler()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
