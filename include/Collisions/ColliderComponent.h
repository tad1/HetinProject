#pragma once
#include "../Component.h"

class ColliderComponent : public Component{
public:
	Vector2 offset;
	Collider * collider;

	void OnCollisionEnter(ColliderComponent& col) {
		printf("Collision \n");
	} //col stands for collider


	ColliderComponent(Collider data, int layer, Vector2 offset = Vector2(0, 0));
};

