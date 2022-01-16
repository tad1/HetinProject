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
public:

	void Update() {
		Cannon::Update();

		//Check collision
		if (collider.collisionCol != nullptr) {
			Damage(2);
			collider.collisionCol = nullptr;
		}

		if (health <= 0) {
			//Destory
		}

		//Set direction to predicted target next location, and shoot
		shootDirection.x = cosf(angle);
		shootDirection.y = sinf(angle);

		physics->velocity = shootDirection * speed;
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

	EnemyPlane() {
		health = 5; //5 points
		speed = 100.0f; //px per second
		collider.SetCollider(LAYER_ENEMY);
		
		physics = RigidbodyPool.Get(this, &collider);
	}
};