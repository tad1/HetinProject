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
#include "include/SDL_Audio.h"
#include "Player.h"
#include "Cannon.h"
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

	//Testing Stuff
	Cannon cannon;
	//


	Player player;

	SDL_Event event;
	TextRenderer simpleFont;
	Vector2 velocity, acceleration;

	CloudPool backgroundClouds;
	CloudPool midgroundClouds;

	double GameTime = 0.0;
	int score = 10;
	
public:
	void start() {
		//Prepare
		Init();
		

		//Run game loop
		while (playing) {

			SDL_PollEvent(&event);
			Time.calculateDelta();
			inputUpdate();

			while (Time.fixedUnscaledTime + Time.fixedUnscaledDeltaTime <= Time.unscaledTime) {
				Time.calculateFixedTime();
				physicsUpdate();
			}

			update();
			Input.updatePreviousInput();
			render();

		}


	}

private:

	void Init() {
		WAV_File soundtrack = WAV_Loader.Add("./assets/music/luft.wav");
		Audio.Play(soundtrack);


		playerBullets.sprite.Load("./assets/sprites/bullet.bmp");
		enemyBullets.sprite.Load("./assets/sprites/bullet.bmp");

		player.Init();

		cannon.SetTarget(&player);
		cannon.Init("./assets/sprites/cannon.bmp", 0.2f, 1.6f, 4, 200.0f);
		cannon.transform.position = Vector2(500, 500);

		backgroundClouds.Init("./assets/sprites/bgclouds.bmp", 9);
		midgroundClouds.Init("./assets/sprites/fgclouds.bmp", 8);
		backgroundClouds.SetParalaxLevel(0.5f);
		backgroundClouds.SetColorMod(colors[HEALTH_COLOR]);

		simpleFont.Load("./assets/sprites/font.bmp");
		simpleFont.SetColor(colors[colorNames::PRIMARY_COLOR]);
		mainCamera.target = &player.transform;
		playing = true;
	}

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


		playerBullets.Update();
		enemyBullets.Update();
		player.Update();
		cannon.Update();

		backgroundClouds.Update();
		midgroundClouds.Update();
		mainCamera.Update();
	}

	void render() {
		backgroundClouds.Render();
		midgroundClouds.Render();

		//render all objects from the render list
		cannon.Render();
		
		player.Render();
		

		//Render Bullets
		playerBullets.Render();
		enemyBullets.Render();

		//render GUI
		simpleFont.Render("SCORE", GridVector(860, 10), 3);
		simpleFont.Render((char*)String::ToString<int>(score), GridVector(890, 40), 2);
		simpleFont.Render((char *)String::ToString(3,"TIME: ",String::ToString<double>(GameTime),"s"), GridVector(100, 10), 2);

#ifdef DRAW_COLLIDERS
		
#endif // DRAW_COLLIDERS


		ScreenHandleler::Render();
	}

	void physicsUpdate() {

		playerBullets.PhysicsUpdate();
		enemyBullets.PhysicsUpdate();
		player.PhysicsUpdate();
		//update every gameObject
		RigidbodyPool.FixedUpdate();

		/*velocity += acceleration * Time.fixedDeltaTime;
		acceleration = acceleration * 0.96f;
		velocity = velocity * 0.95f;*/

	}

	void inputUpdate() {
		
		
		if (Input.isKeyJustPressed(SDL_SCANCODE_T)) {
			Time.setTimeScale(0.2f);
		}
		if (Input.isKeyJustPressed(SDL_SCANCODE_U)) {
			Time.setTimeScale(-0.2f);
		}
		if (Input.isKeyJustPressed(SDL_SCANCODE_Y)) {
			Time.setTimeScale(1.0f);
		}

		if (Input.isKeyJustPressed(SDL_SCANCODE_N)) {
			Console.Log("Started new game!");
			velocity = Vector2(0, 0);
			acceleration = Vector2(0, 0);
			GameTime = 0.0;
		}

		if (Input.isKeyJustPressed(SDL_SCANCODE_D)) {
			velocity = Vector2(0,0);
		}
		if (event.type == SDL_QUIT || Input.isKeyJustPressed(SDL_SCANCODE_ESCAPE)) {
			exit();
		}
	}

	


};