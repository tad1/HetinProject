#pragma once
#include "include/GenericPool.h"
#include "libs/Vector2.h"
#include "include/Component.h"
#include "include/CollisionSystem.h"
#include "Time.h"
#include "include/Physics2D.h"


/// <summary>
/// Component which update GameObject position, and collider position if is passed
/// </summary>
class RigidbodyComponent : public Component{
	ColliderComponent* collider;
	
public:
	Vector2 velocity;
	bool useGravity;

	void FixedUpdate() {
		Vector2 moveDelta = velocity * Time.fixedDeltaTime * sign(Time.timeScale);
		gameObject->transform.Translate(moveDelta);
		if (collider != nullptr && collider->collider != nullptr) {
			collider->collider->circle.x += moveDelta.x;
			collider->collider->circle.y += moveDelta.y;
		}
	}

	void SetCollider(ColliderComponent* collider_ = nullptr) {
		collider = collider_;
	}

	RigidbodyComponent(ColliderComponent* collider_ = nullptr) {
		collider = collider_;
	}
};

/// <summary>
/// Selfcare RigidBodyComponent object pool
/// </summary>
class RigidbodyComponentPool : public GenericPool<RigidbodyComponent, 2000> {
public:
	RigidbodyComponent* Get(GameObject* instance, ColliderComponent* collider_ = nullptr) {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (!inUse[i]) {
				inUse[i] = true;
				pool[i].gameObject = instance;
				pool[i].SetCollider(collider_);
				pool[i].velocity = Vector2(0, 0);
				return &pool[i];
			}
		}
		return nullptr;
	}

	/// <summary>
	/// Return Component to pool
	/// </summary>
	/// <param name="component"></param>
	void Return(RigidbodyComponent* component) {
		int index = pool - component;
		if (index < 0 || index >= POOL_SIZE) return;
		inUse[index] = false;
	}

	/// <summary>
	/// Updates RigidBodyComponent with FixedDeltaTime
	/// </summary>
	void FixedUpdate() {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (inUse[i]) {
				pool[i].FixedUpdate();
			}
		}
	}
};
static RigidbodyComponentPool RigidbodyPool;