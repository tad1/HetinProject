#pragma once
#include "include/GameObject.h"
#include "include/CollisionSystem.h"
#include "SpriteRendererComponent.h"
#include "PhysicsComponent.h"
#include "Projectiles.h"
#include "Cannon.h"


//Ship have 11 frames
class Enemy : public GameObject {
	ColliderComponent collider;
	RigidbodyComponent* physics;
	SpriteSheetAnimationRenderer spriteRenderer;

};