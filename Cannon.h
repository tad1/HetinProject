#pragma once
#include "include/GameObject.h"
#include "Projectiles.h"
#include "SpriteRendererComponent.h"
#include "Time.h"
#include "Player.h"
#include "libs/Math.h"

/// <summary>
/// GameObject that aim next target position, and shoot relevant cannon to setting (shooting pattern)
/// </summary>
class Cannon : public GameObject {
protected:
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

	/// <summary>
	/// Setup cannon settings; shoot, patttern delay (in seconds), and bullet speed (pixels per seconds)
	/// </summary>
	/// <param name="spritePath"></param>
	/// <param name="shootDelay_"></param>
	/// <param name="patterDelay_"></param>
	/// <param name="patternShoots_"></param>
	/// <param name="bulletSpeed_"></param>
	void Init(char* spritePath, float shootDelay_, float patterDelay_, int patternShoots_, float bulletSpeed_) {
		sprite.Load(spritePath);
		shootTimer = shootDelay = shootDelay_;
		patternTimer = patternDelay = patterDelay_;
		shootsLeft = patternShoots = patternShoots_;
		bulletSpeed = bulletSpeed_;
		cannonSpeed = 2;
	}

	void Update() {
		//update timers
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
			targetNextPosition += target->getVelocity() * time; //Predict next position relative to bullet reach time
			distance = Vector2::Distance(position, targetNextPosition);

			//Set angle
			float angleDelta = atan2(distance.y, distance.x) - angle;
			if (angleDelta < 0) {
				angleDelta += radianConst;
			}
			angleDelta = angleDelta * Time.deltaTime * cannonSpeed;
			//angleDelta = clamp(angleDelta, -cannonSpeed, cannonSpeed);
			angle += angleDelta;


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