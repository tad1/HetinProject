#pragma once
#include "include/GameObject.h"
#include "Projectiles.h"
#include "SpriteRendererComponent.h"
#include "Time.h"
#include "Player.h"

class Cannon : public GameObject {
	SpriteRenderer sprite;

	float cannonSpeed;
	float bulletSpeed;
	double angle;

	float shootTimer;
	float shootDelay;

	float patternTimer;
	float patternDelay;
	int shootsLeft;
	int patternShoots;

	Vector2 shootDirection;

	Player* target;
public:

	void SetTarget(Player* newTarget) {
		target = newTarget;
	}

	void Init(char* spritePath, float shootDelay_, float patterDelay_, int patternShoots_, float bulletSpeed_) {
		sprite.Load(spritePath);
		shootTimer = shootDelay = shootDelay_;
		patternTimer = patternDelay = patterDelay_;
		shootsLeft = patternShoots = patternShoots_;
		bulletSpeed = bulletSpeed_;
	}

	void Update() {
		shootTimer -= Time.deltaTime;
		if (shootTimer < 0) {
			shootTimer = 0;
		}
		patternTimer -= Time.deltaTime;
		if (patternTimer < 0) {
			patternTimer = 0;
		}

		if (target != nullptr) {
			//Predict players position
			Vector2 position = transform.WorldPosition();
			Vector2 targetNextPosition = target->transform.position;
			Vector2 distance = Vector2::Distance(position, targetNextPosition);
			float time = distance.Magnitude() / bulletSpeed; //Number of seconds to hit target
			targetNextPosition += target->getVelocity() * time;
			distance = Vector2::Distance(position, targetNextPosition);
			//Set angle
			angle = atan2(distance.y, distance.x);


			//check if can shoot
			if (shootTimer <= 0 && patternTimer <= 0) {
				shootTimer += shootDelay;
				shootsLeft--;
				Shoot();

				if (shootsLeft <= 0) {
					shootsLeft += patternShoots;
					patternTimer += patternDelay;
				}
			}
		}
	}

	void Render() {
		sprite.Render(transform.WorldPosition(), angle * radianConst);
	}

	void Shoot() {
		shootDirection.x = cosf(angle);
		shootDirection.y = sinf(angle);

		enemyBullets.Projectile(transform.WorldPosition(), shootDirection * bulletSpeed);
	}
};