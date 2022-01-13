// HetinProject.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "HetinProject.h"
#include "include/GameObject.h"
#include "include/ScreenHandleler.h"
#include "TextureManager.h"
#include "tests/tests.h"
#include "ColorPalete.h"
#include "Camera.h"

using namespace std;

Game game;

int main(int argc, char* argv[])
{

	testAll();
	ScreenHandleler::Initialize("Hetin",Vector2T<int>(1000,600));
	ScreenHandleler::SetBackgroundColor(colors[colorNames::SECONDARY_COLOR]);
	
	mainCamera.SetSize(ScreenHandleler::GetWindowSize());

	game.start();
	

	return 0;
}



/*

SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = nullptr;

	window = SDL_CreateWindow("HetinProject", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning) {

		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

*/