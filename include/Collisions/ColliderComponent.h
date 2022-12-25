#pragma once
#include "../Component.h"

class ColliderComponent : public Component{
public:
	Vector2 offset;
	Collider * collider;
	ColliderComponent* collisionCol;

	void OnCollisionEnter(ColliderComponent* other) {
		if (collider == nullptr) return;
		collisionCol = other;
		if(other != nullptr)
			other->collisionCol = this;
	} 


	ColliderComponent(Collider data, int layer, Vector2 offset = Vector2(0, 0));
	ColliderComponent() {
		name = "collider";
		collisionCol = nullptr;
		offset = Vector2(0, 0);
		collider = nullptr;
	}
	ColliderComponent(int layer);

	bool CompareTag(char* tag) {
		if (gameObject == nullptr) return false;
		return strcmp(gameObject->tag, tag) == 0;
	}

	/// <summary>
	/// Setup collider for given layer
	/// </summary>
	/// <param name="layer"></param>
	bool SetCollider(int layer);
};

