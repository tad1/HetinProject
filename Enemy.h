#pragma once
#include "include/GameObject.h"
#include "include/CollisionSystem.h"
#include "SpriteRendererComponent.h"
#include "PhysicsComponent.h"
#include "Projectiles.h"
#include "Cannon.h"


//NOTE: Ship have 11 frames

/// <summary>
/// Not implemented class of enemy ship
/// </summary>
class EnemyShip : public GameObject {
	ColliderComponent collider;
	RigidbodyComponent* physics;
	SpriteSheetAnimationRenderer spriteRenderer;

};