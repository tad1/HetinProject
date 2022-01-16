// HetinProject.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "main.h"
#include "include/GameObject.h"
#include "include/ScreenHandleler.h"
#include "TextureManager.h"
#include "tests/tests.h"
#include "ColorPalete.h"
#include "Camera.h"
#include <crtdbg.h>

using namespace std;

Game game;

int main(int argc, char* argv[])
{
#if ENABLE_UNIT_TESTS
	testAll();
#endif
	ScreenHandleler::Initialize("Hetin",Vector2T<int>(1000,700));
	ScreenHandleler::SetBackgroundColor(colors[colorNames::SECONDARY_COLOR]);
	
	mainCamera.SetSize(ScreenHandleler::GetWindowSize());

	game.start();
	_CrtDumpMemoryLeaks();

	return 0;
}
