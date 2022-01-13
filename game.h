#include <SDL.h>
#include <stdio.h>
#include "SpriteRendererComponent.h"
#include "include/CollisionSystem.h"
#include "Time.h"
#include "Input.h"
#include "TextRenderer.h"
#include "Console.h"
#include "ColorPalete.h"
#include "Camera.h"
#include "Clouds.h"
//The level file
/*
	Level Name




*/

/*
Loading level.
Get assets -> Execute

*/


class Game{


private:
	SDL_Event event;
	SpriteSheetAnimationRenderer eti;
	SpriteRenderer prop;
	TextRenderer simpleFont;
	Transform transform;
	Vector2 frame;
	Vector2 velocity, acceleration;
	SDL_Color white{ 255,255,255,255 };
	SDL_Color black{ 0,0,0,255 };

	CloudPool backgroundClouds;
	CloudPool midgroundClouds;

	double angle = 0.0;
	double GameTime = 0.0;
	int score = 10;
	
public:
	void start() {
		//Prepare
		backgroundClouds.Init("./assets/sprites/bgclouds.bmp", 9);
		midgroundClouds.Init("./assets/sprites/bgclouds.bmp", 9);
		backgroundClouds.SetParalaxLevel(0.5f);
		backgroundClouds.SetColorMod(colors[HEALTH_COLOR]);

		eti.Load("./assets/sprites/plane.bmp", GridVector(4, 1));
		prop.Load("./assets/sprites/bullet.bmp");
		simpleFont.Load("./assets/sprites/font.bmp");
		simpleFont.SetColor(colors[colorNames::PRIMARY_COLOR]);
		frame = GridVector(0,0);
		velocity = Vector2(0, 0);
		transform.position = Vector2(200, 200);
		mainCamera.target = &transform;
		acceleration = Vector2(0, 0);
		playing = true;

		//Run game loop
		while (playing) {

			SDL_PollEvent(&event);
			Time.calculateDelta();
			inputUpdate();

			while (Time.fixedTime + Time.fixedDeltaTime <= Time.time) {
				Time.calculateFixedTime();
				physicsUpdate();
			}

			update();
			Input.updatePreviousInput();
			render();

		}


	}

private:

	

	bool playing;
	void exit() {
		playing = false;
	}

	void update() {
		GameTime += Time.deltaTime;

		/*if ((int)(Time.time * 50) % 4 > 1) {
			simpleFont.SetColor(white);
		}
		else {
			simpleFont.SetColor(black);
		}*/

		//Update every gameobject


		int deg = angle * (180.0 / M_PI);
		deg = ((deg - 67) % 180);
		deg = deg < 0 ? deg + 180 : deg;
		if (deg < 45) {
			frame = GridVector(0, 0);
		}
		else if (deg < 90) {
			frame = GridVector(1, 0);
		}
		else if (deg < 135) {
			frame = GridVector(2, 0);
		}
		else {
			frame = GridVector(3, 0);
		}
		

		backgroundClouds.Update();
		midgroundClouds.Update();
		mainCamera.Update();
	}

	void render() {
		backgroundClouds.Render();
		midgroundClouds.Render();

		//render all objects from the render list
		eti.Render(transform.position,frame, angle * (180.0 / M_PI));
		prop.Render(GridVector(2000, 500));
		prop.Render(GridVector(100, 100));
		prop.Render(GridVector(200, 200));
		prop.Render(GridVector(300, 300));
		prop.Render(GridVector(400, 400));
		prop.Render(GridVector(500, 500));

		//render GUI
		simpleFont.Render("SCORE", GridVector(860, 10), 3);
		simpleFont.Render((char*)String::ToString<int>(score), GridVector(890, 40), 2);
		simpleFont.Render((char *)String::ToString(3,"TIME: ",String::ToString<double>(GameTime),"s"), GridVector(100, 10), 2);

#ifdef DRAW_COLLIDERS
		
#endif // DRAW_COLLIDERS


		ScreenHandleler::Render();
	}

	void physicsUpdate() {



		//update every gameObject

		transform.position += Vector2(0, 1) * 98.0f * 0.32f * Time.fixedDeltaTime;
		velocity += acceleration * Time.fixedDeltaTime;
		Vector2 direction;
		direction.x = velocity.Magnitude() * (cosf(angle));
		direction.y = velocity.Magnitude() * (sinf(angle));
		transform.position += direction * 100.0f * Time.fixedDeltaTime;
		acceleration = acceleration * 0.96f;
		velocity = velocity * 0.95f;

	}

	void inputUpdate() {
		
		
		if (Input.isKeyPressed(SDL_SCANCODE_W) 
			|| Input.isKeyPressed(SDL_SCANCODE_UP)) {
			acceleration = Vector2(0, -4);
		}

		if (Input.isKeyPressed(SDL_SCANCODE_A)
			|| Input.isKeyPressed(SDL_SCANCODE_LEFT)) {
			angle -= 4.0 * Time.deltaTime;
		}

		if (Input.isKeyPressed(SDL_SCANCODE_D)
			|| Input.isKeyPressed(SDL_SCANCODE_RIGHT)) {
			angle += 4.0 * Time.deltaTime;

		}

		if (Input.isKeyJustPressed(SDL_SCANCODE_N)) {
			Console.Log("Started new game!");
			velocity = Vector2(0, 0);
			acceleration = Vector2(0, 0);
			angle = 0;
			GameTime = 0.0;
			transform.position = Vector2(2000, 500);
		}

		if (Input.isKeyJustPressed(SDL_SCANCODE_D)) {
			velocity = Vector2(0,0);
		}
		if (event.type == SDL_QUIT || Input.isKeyJustPressed(SDL_SCANCODE_ESCAPE)) {
			exit();
		}
	}

	


};