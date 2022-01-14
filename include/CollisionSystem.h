#pragma once

#include "Collisions/Layers.h"
#include "Collisions/Colliders.h"
#include "Collisions/ColliderComponent.h"
#include "Collisions/CollidersManager.h"

ColliderComponent::ColliderComponent(Collider data, int layer, Vector2 offset)
{
	name = "unnamed";
	collisionCol = nullptr;
	data.circle.x += offset.x;
	data.circle.y += offset.y;
	collider = ColliderManager.Get(layer);
	*collider = data;
}

ColliderComponent::ColliderComponent(int layer)
{
	name = "collider";
	collisionCol = nullptr;
	collider = ColliderManager.Get(layer);
}

void ColliderComponent::SetCollider(int layer) {
 	collider = ColliderManager.Get(layer);
}