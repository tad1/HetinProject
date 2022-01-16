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

	bool playing;
	Cannon cannon;

	Player player;
	EnemyPlane plane;
	SpriteRenderer healthBackground;
	SpriteRenderer sea;
	WAV_File soundtrack;

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

		onExit();


	}

private:
	/// <summary>
	/// Awake function - the function that is executed at the beginning of the game
	/// </summary>
	void init() {
		ScreenHandleler::SetBackgroundColor(colors[SECONDARY_COLOR]);

#if !(DISABLE_AUDIO)
		soundtrack = WAV_Loader.Add("./assets/music/luft.wav");
		Audio.Play(soundtrack);
#endif


		playerBullets.sprite.Load("./assets/sprites/bullet.bmp");
		enemyBullets.sprite.Load("./assets/sprites/bullet.bmp");

		healthBackground.Load("./assets/sprites/white.bmp");
		healthBackground.Color(colors[HEALTH_COLOR]);

		sea.Load("./assets/sprites/sea.bmp");

		player.Init();

		cannon.SetTarget(&player);
		// Shoot with .2s delay, pattern delay is 1.6s and is contain 4 bullet shoots; bullet speed is 200px per second
		cannon.Init("./assets/sprites/cannon.bmp", 0.2f, 1.6f, 4, 200.0f);
		cannon.transform.position = Vector2(500, 500); //Random position

		plane.SetTarget(&player);
		// Shoot with 1s delay, with no pattern delay; bullet speed is 200px per second
		plane.Init("./assets/sprites/eplane.bmp", 1.0f, 0.0f, 1, 200.0f);
		plane.SetPosition(Vector2(2000, 700)); //Random position
		

		backgroundClouds.Init("./assets/sprites/bgclouds.bmp", 9); //9 types of clouds on spritesheet
		midgroundClouds.Init("./assets/sprites/fgclouds.bmp", 8); //8 types of clouds on spritesheet
		backgroundClouds.SetParalaxLevel(0.5f); //Background clouds will move 0.5x times slower
		backgroundClouds.SetColorMod(colors[HEALTH_COLOR]);

		simpleFont.Load("./assets/sprites/font.bmp");
		simpleFont.SetColor(colors[colorNames::PRIMARY_COLOR]);
		mainCamera.target = &player.transform;
		playing = true;
	}

	/// <summary>
	/// Function executed before termination of the program
	/// </summary>
	void onExit() {
		TextureManager.DeleteAll();
		WAV_Loader.DeleteAll();
	}

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

		char* scoreText = ToString(score);
		char* timeStr = ToString(GameTime);
		char* timeText = ConcatString(3, "TIME: ", timeStr, "s");
		simpleFont.Render(scoreText, GridVector(890, 40), 2);
		simpleFont.Render(timeText, GridVector(100, 10), 2);
		delete[] scoreText;
		delete[] timeStr;
		delete[] timeText;
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

	/// <summary>
	/// Called at the beginning of frame
	/// </summary>
	void inputUpdate() {
		
		if (Input.isKeyJustPressed(SDL_SCANCODE_N)) {
			reset();
			GameTime = 0.0;
			Time.setTimeScale(1.0f);
		}

		if (event.type == SDL_QUIT || Input.isKeyJustPressed(SDL_SCANCODE_ESCAPE)) {
			exit();
		}
	}

	/// <summary>
	/// Resets game
	/// </summary>
	void reset() {
		// Clears all bullets in game
		playerBullets.Reset();
		enemyBullets.Reset();

		plane.SetPosition(Vector2(2000, 700)); //Random position

		player.Reset();

#if !(DISABLE_AUDIO)
		Audio.Stop();
		Audio.Play(soundtrack);
#endif

		player.Init();

	}
	


};