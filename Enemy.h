#pragma once
#include "include/GameObject.h"
#include "include/CollisionSystem.h"
#include "SpriteRendererComponent.h"
#include "PhysicsComponent.h"
#include "Projectiles.h"
#include "Cannon.h"
#include "include/MonoBechaviour.h"
#include "libs/Random.h"

//NOTE: Ship have 11 frames

/// <summary>
/// Not implemented class of enemy ship
/// </summary>
class EnemyShip : public MonoBechaviour {
	ColliderComponent collider;
	RigidbodyComponent* physics;
	SpriteSheetAnimationRenderer spriteRenderer;
	GridVector frame;
	int maxFrames;
	Cannon cannon;
	int health;
	float speed;
	float playerHitMaxTime, playerHitTimer;
	float secondsPerFrame, frameTimer;
	
public:

	void Awake() {
		
	}

	EnemyShip() {
		cannon.transform.SetParent(transform);
		cannon.transform.Translate(Vector2(15, 20));
	}

	bool Create() {

		secondsPerFrame = 0.2f;
		frameTimer = secondsPerFrame;


		playerHitMaxTime = 0.3f; //0.3s
		playerHitTimer = playerHitMaxTime;

		health = 8;
		speed = Random::Number(20, 30);


		if (collider.SetCollider(LAYER_ENEMY)) {
			physics = RigidbodyPool.Get(this, &collider);
			physics->velocity = (Random::Number(2) == 0 ? -1 : 1) * speed;
			return true;
		}

		setRectCollider(*collider.collider, 0, 0, 10, 10);
		return false;

	}

	void Render() {
		spriteRenderer.Render(transform.position, frame);
		cannon.Render();
	}

	void SetPosition(Vector2 position) {
		transform.position = position;
		if (collider.collider != nullptr) {
			Vector2 colliderPosition = transform.position;
			setRectCollider(*collider.collider, colliderPosition.x, colliderPosition.y, 64, 32);
		}
	}

	void Destroy() {
		RigidbodyPool.Return(physics);
		ColliderManager.Return(collider.collider, LAYER_ENEMY);
		collider.collider = nullptr;
		physics = nullptr;
	}

	void Init() {
		maxFrames = 11;
		spriteRenderer.Load("./assets/sprites/ship.bmp", GridVector(maxFrames, 1));
	}

	bool isAlive() {
		return health > 0;
	}

	void SetTarget(Player* player) {
		cannon.SetTarget(player);
	}

	void InitCannon(char* spritePath, float shootDelay_, float patterDelay_, int patternShoots_, float bulletSpeed_) {
		cannon.Init(spritePath, shootDelay_, patterDelay_, patternShoots_, bulletSpeed_);
	}

	void Update() {
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
		
		cannon.Update();

		//Update Animation
		frameTimer -= Time.deltaTime;
		if (frameTimer < 0) {
			frameTimer += secondsPerFrame;
			frame += Vector2(1, 0);
			if (frame.x >= maxFrames) {
				frame.x = 0;
			}
		}

	}

	void Damage(int value) {
		health -= value;
	}



};