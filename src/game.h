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
#include "ParticleSystem.h"
#include "EnemySpawner.h"
#include "Menu.h"

class Game {


private:

	bool playing;

	ParticleSystem<1> gradeParticle;

	Menu* mainMenu;
	Player player;
	EnemyPlaneSpawner enemySpawner;
	EnemyShipSpawner shipSpawner;
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
		mainMenu = new Menu();
		mainMenu->Awake();

#if !(DISABLE_AUDIO)
		soundtrack = WAV_Loader.Add("./assets/music/luft.wav");
		Audio.Play(soundtrack);
		Audio.Pause();
#endif

		gradeParticle.Load("./assets/sprites/grade.bmp", 5);
		gradeParticle.RenderOnScreen();

		explosions.Load("./assets/sprites/boom.bmp", 7);

		playerBullets.sprite.Load("./assets/sprites/pbullet.bmp");
		enemyBullets.sprite.Load("./assets/sprites/bullet.bmp");

		healthBackground.Load("./assets/sprites/white.bmp");
		healthBackground.Color(colors[HEALTH_COLOR]);

		sea.Load("./assets/sprites/sea.bmp");

		player.Init();

		enemySpawner.Init("./assets/sprites/eplane.bmp", &player, 2.0f);
		// Shoot with 1s delay, with no pattern delay; bullet speed is 200px per second
		shipSpawner.Init(&player);


		backgroundClouds.Init("./assets/sprites/bgclouds.bmp", 9); //9 types of clouds on spritesheet
		midgroundClouds.Init("./assets/sprites/fgclouds.bmp", 8); //8 types of clouds on spritesheet
		backgroundClouds.SetParalaxLevel(0.5f); //Background clouds will move 0.5x times slower
		backgroundClouds.SetColorMod(colors[HEALTH_COLOR]);



		simpleFont.Load("./assets/sprites/font.bmp");
		simpleFont.SetColor(colors[colorNames::PRIMARY_COLOR]);
		mainCamera.target = &player;
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

		//Update every gameobject

		mainScore.update();
		playerBullets.Update();
		enemyBullets.Update();
		player.Update();

		enemySpawner.Update();
		shipSpawner.Update();

		backgroundClouds.Update();
		midgroundClouds.Update();
		mainCamera.Update();

		if (mainMenu->isActive()) {
			mainMenu->Update();
		}
	}

	/// <summary>
	/// Called at the end of the frame
	/// </summary>
	void render() {

		healthBackground.RenderScaledCentered(mainCamera.transform.position, LEVEL_WIDTH);
		player.RenderHealth();
		backgroundClouds.Render();

		midgroundClouds.Render();

		if (!mainMenu->isActive()) {
			//render all objects from the render list
			shipSpawner.Render();
			enemySpawner.Render();
			player.Render();
			explosions.Animate();
		}

		//Render Bullets
		playerBullets.Render();
		enemyBullets.Render();

		//sea.RenderScaled(Vector2(0, LEVEL_HEIGHT - SEA_LEVEL), GridVector(LEVEL_WIDTH, 6));


		//render GUI
		if (mainMenu->isActive()) {
			mainMenu->Render();
		}
		else {

			simpleFont.Render("SCORE", GridVector(860, 10), 3);

			char* scoreText = ToString(mainScore.getScore());
			char* timeStr = ToString(GameTime);
			char* timeText = ConcatString(3, "TIME: ", timeStr, "s");
			char* comboValue = ToString(mainScore.getCombo());
			char* comboText = ConcatString(2, "x", comboValue);

			float comboTextSize = 2 + mainScore.getComboTimeNormalized() * 2;

			simpleFont.Render(scoreText, GridVector(890, 40), 2);
			simpleFont.Render(comboText, GridVector(890, 70), comboTextSize);
			simpleFont.Render(timeText, GridVector(500, 10), 2);
			simpleFont.Render(mainScore.getGrade(), GridVector(50, 10), 4);
			delete[] scoreText;
			delete[] timeStr;
			delete[] timeText;
			delete[] comboValue;
			delete[] comboText;

			if (mainScore.gradeChanged()) {
				gradeParticle.Create(GridVector(30, 0), Vector2(0, 0));
			}
			gradeParticle.Animate();
		}



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
		if (Input.isKeyJustPressed(SDL_SCANCODE_L)) {
			mainScore.addScore(100);
		}
		if (Input.isKeyJustPressed(SDL_SCANCODE_N)) {
			reset();
			GameTime = 0.0;
			Time.setTimeScale(1.0f);
		}
		if (Input.isKeyJustPressed(SDL_SCANCODE_Y)) {
			Time.setTimeScale(0.2f);
		}
		if (Input.isKeyJustPressed(SDL_SCANCODE_U)) {
			Time.setTimeScale(-0.2f);
		}
		if (Input.isKeyJustPressed(SDL_SCANCODE_I)) {
			Time.setTimeScale(1);
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

		mainScore.Reset();
		enemySpawner.Reset();

		player.Reset();

#if !(DISABLE_AUDIO)
		Audio.Stop();
		Audio.Play(soundtrack);
#endif

		player.Init();

	}

};