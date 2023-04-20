#pragma once
#include "EnemyPlane.h"
#include "Enemy.h"
#include "include/GenericPool.h"
#include "Time.h"
#include "Player.h"
#include "ParticleSystem.h"
#include "include/Random.h"
#include "Camera.h"
#include "Score.h"
#include "include/SDL_Audio.h"

class EnemyPlaneSpawner : GenericPool<EnemyPlane,30>{

	WAV_File explosionsSFX[3];
	const int explosionSFXCount = 3;

	float spawnTime;
	float spawnTimer;
	SpriteRenderer sprite;
	Player* target;
public:
	void Update() {
		//Spawn
		spawnTimer -= Time.deltaTime;
		if (spawnTimer <= 0) {
			Spawn();
			spawnTimer += spawnTime;
		}

		//Check health
		for (int i = 0; i < POOL_SIZE; i++) {
			if (inUse[i]) {
				if (!pool[i].isAlive()) {
					//Plane is not alive
					mainScore.addScore(20);
					inUse[i] = false;
					pool[i].Destroy();
					explosions.Create(pool[i].transform.position, Vector2(0, 0));

					//Play SFX
					int explosionIndex = Random::Number(explosionSFXCount);
					Audio.PlaySFX(explosionsSFX[explosionIndex]);
				}
				else {
					pool[i].Update();
				}
			}
		}

	}

	void Render() {
		for (int i = 0; i < POOL_SIZE; i++){
			if (inUse[i]) {
				pool[i].Render();
			}
		}
	}

	void Init(char* sprite_path,Player* target,float spawnTime_) {
		spawnTimer = spawnTime = spawnTime_;
		for (int i = 0; i < POOL_SIZE; i++) {
			pool[i].SetTarget(target);
			pool[i].Init(sprite_path, 2.0f, 0, 1, 200.0f);
		}
		for (int i = 0; i < POOL_SIZE; i++) {
			inUse[i] = false;
		}

		explosionsSFX[0] = WAV_Loader.Add("./assets/music/explosion1.wav");
		explosionsSFX[1] = WAV_Loader.Add("./assets/music/explosion2.wav");
		explosionsSFX[2] = WAV_Loader.Add("./assets/music/explosion3.wav");

	}

	void Spawn() {
		int x = Random::Number(0, LEVEL_WIDTH);
		int y = Random::Number(SEA_LEVEL, LEVEL_HEIGHT - SEA_LEVEL);

		//TODO: spawn outsize screen
		for (int i = 0; i < POOL_SIZE; i++) {
			if (!inUse[i]) {
				if (pool[i].Create()) {
				pool[i].SetPosition(Vector2(x, y));
				inUse[i] = true;
				}
				break;
			}
		}
	}

	void Reset() {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (inUse[i]) {
				pool[i].Destroy();
			}
			inUse[i] = false;
		}
	}

};




class EnemyShipSpawner : GenericPool<EnemyShip, 30> {

	WAV_File explosionsSFX[3];
	const int explosionSFXCount = 3;

	float spawnTime;
	float spawnTimer;
	Player* target;
public:
	void Update() {
		//Spawn
		spawnTimer -= Time.deltaTime;
		if (spawnTimer <= 0) {
			Spawn();
			spawnTimer += spawnTime;
		}

		//Check health
		for (int i = 0; i < POOL_SIZE; i++) {
			if (inUse[i]) {
				if (!pool[i].isAlive()) {
					//Plane is not alive
					mainScore.addScore(100);
					inUse[i] = false;
					pool[i].Destroy();
					explosions.Create(pool[i].transform.position, Vector2(0, 0));

					//Play SFX
					int explosionIndex = Random::Number(explosionSFXCount);
					Audio.PlaySFX(explosionsSFX[explosionIndex]);
				}
				else {
					pool[i].Update();
				}
			}
		}

	}

	void Render() {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (inUse[i]) {
				pool[i].Render();
			}
		}
	}

	void Init(Player* target) {
		spawnTime = 5.0f;
		spawnTimer = spawnTime;
		for (int i = 0; i < POOL_SIZE; i++) {
			pool[i].SetTarget(target);
			pool[i].InitCannon("./assets/sprites/cannon.bmp", 0.2f, 2.0f, 3, 200.0f);
			pool[i].Init();
		}
		for (int i = 0; i < POOL_SIZE; i++) {
			inUse[i] = false;
		}
		explosionsSFX[0] = WAV_Loader.Add("./assets/music/explosion1.wav");
		explosionsSFX[1] = WAV_Loader.Add("./assets/music/explosion2.wav");
		explosionsSFX[2] = WAV_Loader.Add("./assets/music/explosion3.wav");

	}

	void Spawn() {
		int x = Random::Number(0, LEVEL_WIDTH);

		//TODO: spawn outsize screen
		for (int i = 0; i < POOL_SIZE; i++) {
			if (!inUse[i]) {
				if (pool[i].Create()) {
					pool[i].SetPosition(Vector2(x, LEVEL_HEIGHT - SEA_LEVEL - 32));
					inUse[i] = true;
				}
				break;
			}
		}
	}

	void Reset() {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (inUse[i]) {
				pool[i].Destroy();
			}
			inUse[i] = false;
		}
	}

};
