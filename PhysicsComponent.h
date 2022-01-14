#pragma once
#include "include/GenericPool.h"
#include "libs/Vector2.h"
#include "include/Component.h"
#include "include/CollisionSystem.h"
#include "Time.h"
#include "include/Physics2D.h"

class RigidbodyComponent : public Component{
	ColliderComponent* collider;
	
public:
	Vector2 velocity;
	bool useGravity;

	void FixedUpdate() {
		//if (useGravity) velocity += (Vector2)gravity * 1300.0f * Time.fixedDeltaTime;

		Console.Log(velocity.ToString());
		Vector2 moveDelta = velocity * Time.fixedDeltaTime * sign(Time.timeScale);
		gameObject->transform.Translate(moveDelta);
		if (collider != nullptr) {
			collider->collider->circle.x += moveDelta.x;
			collider->collider->circle.y += moveDelta.y;
		}
	}

	RigidbodyComponent(ColliderComponent* collider_ = nullptr) {
		collider = collider_;
	}
};

class RigidbodyComponentPool : public GenericPool<RigidbodyComponent, 1000> {
public:
	RigidbodyComponent* Get(GameObject* instance, ColliderComponent* collider_ = nullptr) {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (!inUse[i]) {
				inUse[i] = true;
				pool[i].gameObject = instance;
				pool[i].velocity = Vector2(0, 0);
				return &pool[i];
			}
		}
		return nullptr;
	}

	void Return(RigidbodyComponent* component) {
		int index = pool - component;
		if (index < 0 || index >= POOL_SIZE) return;
		inUse[index] = false;
	}

	void FixedUpdate() {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (inUse[i]) {
				pool[i].FixedUpdate();
			}
		}
	}
} RigidbodyPool;