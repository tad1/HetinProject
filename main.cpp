// HetinProject.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "main.h"
#include "include/GameObject.h"
#include "include/ScreenHandleler.h"
#include "TextureManager.h"
#include "tests/tests.h"
#include "ColorPalete.h"
#include "Camera.h"
#include "ParticleSystem.h"

using namespace std;

Game game;


void Camera::Update()
{
	//Follow target
	if (target) {
		Vector2 targetPosition = target->transform.position;
		transform.position = targetPosition;
		//transform.position -= target->getVelocity() * Time.deltaTime * 10;
	}
	//Clamp
	transform.position.x = clamp<float>(transform.position.x, size.x, LEVEL_WIDTH - size.x);
	transform.position.y = clamp<float>(transform.position.y, size.y, LEVEL_HEIGHT - size.y);

}


int main(int argc, char* argv[])
{
#if ENABLE_UNIT_TESTS
	testAll();
#endif
	ScreenHandleler::Initialize("Hetin",Vector2T<int>(SCREEN_WIDTH,SCREEN_HEIGHT));
	ScreenHandleler::SetBackgroundColor(colors[colorNames::SECONDARY_COLOR]);
	
	mainCamera.SetSize(ScreenHandleler::GetWindowSize());

	game.start();

	return 0;
}
