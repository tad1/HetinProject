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
#include "EnemyPlane.h"

class Game{


private:

	Cannon cannon;

	Player player;
	EnemyPlane plane;
	SpriteRenderer healthBackground;
	SpriteRenderer sea;

	SDL_Event event;
	TextRenderer simpleFont;

	CloudPool backgroundClouds;
	CloudPool midgroundClouds;

	double GameTime = 0.0;
	int score = 10;
	
public:
	void start() {
		//Prepare
		init();
		

		//Run game loop
		while (playing) {

			//Get events, and calculate delta time
			SDL_PollEvent(&event);
			Time.calculateDelta();

			//Handle input events
			inputUpdate();

			//For each fixed timestamp update physics (position, and collisions)
			while (Time.fixedUnscaledTime + Time.fixedUnscaledDeltaTime <= Time.unscaledTime) {
				Time.calculateFixedTime();
				physicsUpdate();
			}

			//Update game
			update();
			//Update Input
			Input.updatePreviousInput();
			//Render everything
			render();

		}


	}

private:
	/// <summary>
	/// Awake function - the function that is executed at the beginning of the game
	/// </summary>
	void init() {
		ScreenHandleler::SetBackgroundColor(colors[SECONDARY_COLOR]);

		/*WAV_File soundtrack = WAV_Loader.Add("./assets/music/luft.wav");
		Audio.Play(soundtrack);*/


		playerBullets.sprite.Load("./assets/sprites/bullet.bmp");
		enemyBullets.sprite.Load("./assets/sprites/bullet.bmp");

		healthBackground.Load("./assets/sprites/white.bmp");
		healthBackground.Color(colors[HEALTH_COLOR]);

		sea.Load("./assets/sprites/sea.bmp");

		player.Init();

		cannon.SetTarget(&player);
		cannon.Init("./assets/sprites/cannon.bmp", 0.2f, 1.6f, 4, 200.0f);
		cannon.transform.position = Vector2(500, 500);

		plane.SetTarget(&player);
		plane.Init("./assets/sprites/eplane.bmp", 1.0f, 0.0f, 1, 200.0f);
		plane.SetPosition(Vector2(2000, 700));
		

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

	/// <summary>
	/// Called after physics, and input update
	/// </summary>
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
		plane.Update();

		backgroundClouds.Update();
		midgroundClouds.Update();
		mainCamera.Update();
	}

	/// <summary>
	/// Called at the end of the frame
	/// </summary>
	void render() {

		healthBackground.RenderScaledCentered(mainCamera.transform.position, LEVEL_WIDTH);
		player.RenderHealth();
		backgroundClouds.Render();

		midgroundClouds.Render();

		//render all objects from the render list
		cannon.Render();
		plane.Render();
		player.Render();
		

		//Render Bullets
		playerBullets.Render();
		enemyBullets.Render();

		sea.RenderScaled(Vector2(0, LEVEL_HEIGHT - SEA_LEVEL), GridVector(LEVEL_WIDTH, 6));


		//render GUI
		simpleFont.Render("SCORE", GridVector(860, 10), 3);
		simpleFont.Render((char*) ToString(score), GridVector(890, 40), 2);
		simpleFont.Render((char *)ConcatString(3,"TIME: ",ToString(GameTime),"s"), GridVector(100, 10), 2);
#if DRAW_COLLIDERS
		ColliderManager.Draw();
#endif // DRAW_COLLIDERS


		ScreenHandleler::Render();
	}

	/// <summary>
	/// Called at fixed timestep typically 0.01s
	/// </summary>
	void physicsUpdate() {

		playerBullets.PhysicsUpdate();
		enemyBullets.PhysicsUpdate();
		player.PhysicsUpdate();
		//update every gameObject
		RigidbodyPool.FixedUpdate();

		//Check collisions
		ColliderManager.checkAllCollisions();

	}

	void inputUpdate() {
		
		if (Input.isKeyJustPressed(SDL_SCANCODE_N)) {
			reset();
			Console.Log("Started new game!");
			GameTime = 0.0;
		}
		if (Input.isKeyJustPressed(SDL_SCANCODE_T)) {
			Time.setTimeScale(0.2f);
		}
		if (Input.isKeyJustPressed(SDL_SCANCODE_U)) {
			Time.setTimeScale(-0.2f);
		}
		if (Input.isKeyJustPressed(SDL_SCANCODE_Y)) {
			Time.setTimeScale(1.0f);
		}

		if (event.type == SDL_QUIT || Input.isKeyJustPressed(SDL_SCANCODE_ESCAPE)) {
			exit();
		}
	}

	void reset() {
		playerBullets.Reset();
		enemyBullets.Reset();

		plane.SetPosition(Vector2(2000, 700));

		player.Reset();

		/*WAV_File soundtrack = WAV_Loader.Add("./assets/music/luft.wav");
		Audio.Play(soundtrack);*/

		player.Init();

	}
	


};