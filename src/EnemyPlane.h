#pragma once
#include "Cannon.h"
#include "include/CollisionSystem.h"
#include "PhysicsComponent.h"

/// <summary>
/// Enemy plane which in fact.. is actually a flying cannon
/// </summary>
class EnemyPlane : public Cannon {
	ColliderComponent collider;
	RigidbodyComponent* physics;
	int health;
	float speed;
	float playerHitMaxTime, playerHitTimer;

public:

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

			//Set angle
			float angleDelta = atan2(distance.y, distance.x) - angle;
			if (angleDelta < 0) {
				angleDelta += radianConst;
			}
			angleDelta = angleDelta * Time.deltaTime * cannonSpeed;
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

		//Check collision
		playerHitTimer -= Time.deltaTime;
		if (collider.collisionCol != nullptr) {
			if (collider.collisionCol->CompareTag("Player")) {
				//check timer
				if (playerHitTimer < 0) {
					playerHitTimer = playerHitMaxTime;
					Damage(2);
				}
			}
			else {
				Damage(2);
			}
			collider.collisionCol = nullptr;
		}


		//Set direction to predicted target next location, and shoot
		shootDirection.x = cosf(angle);
		shootDirection.y = sinf(angle);
		if (physics != nullptr) {
			physics->velocity = shootDirection * speed;
		}
	}

	void Damage(int value) {
		health -= value;
	}

	void SetPosition(Vector2 position) {
		transform.position = position;
		if (collider.collider != nullptr) {
			Vector2 colliderPosition = transform.position;
			colliderPosition += Vector2(12, 12); //Collider offset - hardcoded value
			collider.collider->circle.x = colliderPosition.x;
			collider.collider->circle.y = colliderPosition.y;
			collider.collider->circle.radius = 12; //Radius of collider - hardcoded value
			collider.collider->circle.flag = CIRCLE_FLAG;
		}
	}

	void Destroy() {
		RigidbodyPool.Return(physics);
		ColliderManager.Return(collider.collider, LAYER_ENEMY);
		collider.collider = nullptr;
		physics = nullptr;
	}

	bool isAlive() {
		return health > 0;
	}

	bool Create() {

		playerHitMaxTime = 0.3f; //0.3s
		playerHitTimer = playerHitMaxTime;

		health = 3; //3 points
		speed = 100.0f; //px per second
		if (collider.SetCollider(LAYER_ENEMY)) {
			physics = RigidbodyPool.Get(this, &collider);
			return true;
		}
		return false;
	}

	void Render() {
		sprite.RenderCentered(transform.WorldPosition(), angle * radianConst, true, true);
	}

	EnemyPlane() {
		cannonSpeed = 4;
	}
};