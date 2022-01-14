#pragma once
#include "include/GenericPool.h"
#include "PhysicsComponent.h"
#include "include/CollisionSystem.h"
#include "SpriteRendererComponent.h"
#include "IDamageable.h"
#include "Settings.h"

//Bullet, the base of all BulletHells
struct Bullet{
	ColliderComponent col;
	Vector2 velocity;
	Vector2 position;
};

template <int layerId, int size>
class BulletPool : public GenericPool<Bullet,size>{
public:
	SpriteRenderer sprite;
	Collider model;
	int layer;

	void Update() {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (inUse[i]) {

				if (pool[i].col.collisionCol != nullptr) {
					ColliderManager.Return(pool[i].col.collider, layer);
					inUse[i] = false;
					continue;
				}
				if (pool[i].position.x < 0 || pool[i].position.y < 0
					|| pool[i].position.x > LEVEL_WIDTH || pool[i].position.y > LEVEL_HEIGHT) {
					//When bullet is out of frame
					ColliderManager.Return(pool[i].col.collider, layer);
					inUse[i] = false;
				}
			}
		}
	}
	void PhysicsUpdate() {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (inUse[i]) {
				Vector2 deltaPosition = pool[i].velocity * Time.fixedDeltaTime;
				pool[i].position += deltaPosition;
				pool[i].col.collider->circle.x += deltaPosition.x;
				pool[i].col.collider->circle.y += deltaPosition.y;
			}
		}
	}

	void Render() {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (inUse[i]) {
				sprite.Render(pool[i].position);
			}
		}
	}

	bool Projectile(Vector2 position_, Vector2 velocity_) {
		static int colliderErrCount = 0;
		printf("Bullet used: %d   time", colliderErrCount);
		for (int i = 0; i < POOL_SIZE; i++) {
			if (!inUse[i]) {
				pool[i].col.SetCollider(layer);
				if (pool[i].col.collider != nullptr) {
				inUse[i] = true;
				pool[i].position = position_;
				pool[i].velocity = velocity_;
				*pool[i].col.collider = model;
				return true;
				}
			}
		}
		return false;
	}

	BulletPool() {
		layer = layerId;
	}
};

BulletPool<LAYER_PLAYER_BULLETS, LAYER_PLAYER_BULLETS_SIZE> playerBullets;
BulletPool<LAYER_ENEMY_BULLETS,LAYER_ENEMY_BULLETS_SIZE> enemyBullets;