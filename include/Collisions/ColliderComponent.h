#pragma once
#include "../Component.h"

class ColliderComponent : public Component{
public:
	Vector2 offset;
	Collider * collider;
	ColliderComponent* collisionCol;

	void OnCollisionEnter(ColliderComponent& col) {
		collisionCol = &col;
		col.collisionCol = this;
		printf("Collision \n");
	} //col stands for collider


	ColliderComponent(Collider data, int layer, Vector2 offset = Vector2(0, 0));
	ColliderComponent() {
		name = "collider";
		collisionCol = nullptr;
		offset = Vector2(0, 0);
		collider = nullptr;
	}
	ColliderComponent(int layer);

	void SetCollider(int layer);
};

