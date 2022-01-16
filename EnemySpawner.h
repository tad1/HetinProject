#pragma once
#include "EnemyPlane.h"
#include "include/GenericPool.h"
#include "Time.h"
#include "Player.h"
#include "ParticleSystem.h"
#include "libs/Random.h"
#include "Camera.h"
#include "Score.h"

class EnemyPlaneSpawner : GenericPool<EnemyPlane,30>{
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
			pool[i].Init(sprite_path, 1.0f, 0, 1, 200.0f);
		}
		for (int i = 0; i < POOL_SIZE; i++) {
			inUse[i] = false;
		}
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

