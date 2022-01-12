#include <SDL.h>
#include <stdio.h>
#include "SpriteRendererComponent.h"
#include "include/CollisionSystem.h"
#include "Time.h"
#include "Input.h"
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
	Vector2 position;
	Vector2 frame;
	Vector2 velocity, acceleration;
	double angle = 0.0;
	
public:
	void start() {
		//Prepare
		eti.Load("./assets/sprites/plane.bmp", GridVector(4, 1));
		frame = GridVector(0,0);
		velocity = Vector2(0, 0);
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
		
	}

	void render() {
		//render all objects from the render list
		eti.Render(position,frame, angle * (180.0 / M_PI));
		ColliderManager.draw();
		ScreenHandleler::Render();
	}

	void physicsUpdate() {
		//update every gameObject

		position += Vector2(0, 1) * 98.0f * 0.32f * Time.fixedDeltaTime;
		velocity += acceleration * Time.fixedDeltaTime;
		Vector2 direction;
		direction.x = velocity.Magnitude() * (cosf(angle));
		direction.y = velocity.Magnitude() * (sinf(angle));
		position += direction * 100.0f * Time.fixedDeltaTime;
		acceleration = acceleration * 0.96f;
		velocity = velocity * 0.95f;

	}

	void inputUpdate() {
		

		if (Input.isKeyPressed(SDL_SCANCODE_W)) {
			acceleration = Vector2(0, -4);
		}

		if (Input.isKeyPressed(SDL_SCANCODE_A)) {
			angle -= 4.0 * Time.deltaTime;
		}

		if (Input.isKeyPressed(SDL_SCANCODE_D)) {
			angle += 4.0 * Time.deltaTime;
		}

		if (Input.isKeyJustPressed(SDL_SCANCODE_R)) {
			velocity = Vector2(0, 0);
			acceleration = Vector2(0, 0);
			angle = 0;
			position = Vector2(200, 30);
		}

		if (Input.isKeyJustPressed(SDL_SCANCODE_D)) {
			velocity = Vector2(0,0);
		}
		if (event.type == SDL_QUIT || Input.isKeyJustPressed(SDL_SCANCODE_ESCAPE)) {
			exit();
		}
	}

	


};