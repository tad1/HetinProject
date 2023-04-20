#pragma once
#include "include/GenericPool.h"
#include "PhysicsComponent.h"
#include "include/CollisionSystem.h"
#include "SpriteRendererComponent.h"
#include "Settings.h"

//Bullet, the base of all BulletHells
struct Bullet{
	ColliderComponent col;
	Vector2 velocity;
	Vector2 position;
};

/// <summary>
/// Semi-selfcare object pool for bullets
/// </summary>
template <int layerId, const int size>
class BulletPool : public GenericPool<Bullet,size>{
public:
	SpriteRenderer sprite;
	Collider model;
	Vector2 offset;
	int layer;

	void Update() {
		for (int i = 0; i < this->POOL_SIZE; i++) {
			if (this->inUse[i]) {

				if (this->pool[i].position.x < 0 || this->pool[i].position.y < 0
					|| this->pool[i].position.x > LEVEL_WIDTH || this->pool[i].position.y > LEVEL_HEIGHT - SEA_LEVEL) {
					//When bullet is out of frame
					ColliderManager.Return(this->pool[i].col.collider, layer);
                    this->pool[i].col.collider = nullptr;
                    this->inUse[i] = false;
				}
			}
		}
	}
	void PhysicsUpdate() {
		for (int i = 0; i < this->POOL_SIZE; i++) {
			if (this->inUse[i]) {
				if (this->pool[i].col.collisionCol != nullptr) {
					//When bullet hitted something
					ColliderManager.Return(this->pool[i].col.collider, layer);
					this->pool[i].col.collider = nullptr;
					this->inUse[i] = false;
					continue;
				}

				//Update bullet and collider position
				Vector2 deltaPosition = this->pool[i].velocity * Time.fixedDeltaTime;
                this->pool[i].position += deltaPosition;
                this->pool[i].col.collider->circle.x += deltaPosition.x;
                this->pool[i].col.collider->circle.y += deltaPosition.y;
			} 
		}
	}

	void Render() {
		for (int i = 0; i < this->POOL_SIZE; i++) {
			if (this->inUse[i]) {
				sprite.Render(this->pool[i].position);
			}
		}
	}

	/// <summary>
	/// Clears all bullets
	/// </summary>
	void Reset() {
		for (int i = 0; i < this->POOL_SIZE; i++) {
            this->inUse[i] = false;
			if (this->pool[i].col.collider != nullptr) {
				ColliderManager.Return(this->pool[i].col.collider, layer);
			}

		}
	}


	/// <summary>
	/// Creates Projectile at given position, with given velocity
	/// </summary>
	bool Projectile(Vector2 position_, Vector2 velocity_) {
		static int colliderErrCount = 0;
		for (int i = 0; i < this->POOL_SIZE; i++) {
			if (!this->inUse[i]) {
                this->pool[i].col.SetCollider(layer);
				if (this->pool[i].col.collider != nullptr) {
					//If there is free collider create bullet
                    this->inUse[i] = true;
                    this->pool[i].position = position_;
                    this->pool[i].velocity = velocity_;
					model.circle.x = position_.x + offset.x;
					model.circle.y = position_.y + offset.y;
					model.component = &this->pool[i].col;
					*this->pool[i].col.collider = model;
					return true;
				}
			}
		}
		return false;
	}

	BulletPool() {
		layer = layerId;
		model.circle.radius = 8;
		model.circle.flag = CIRCLE_FLAG;
		offset = Vector2(8, 8);
	}
};

BulletPool<LAYER_PLAYER_BULLETS, LAYER_PLAYER_BULLETS_SIZE> playerBullets;
BulletPool<LAYER_ENEMY_BULLETS,LAYER_ENEMY_BULLETS_SIZE> enemyBullets;