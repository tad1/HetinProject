#pragma once
#include "include/GameObject.h"
#include "include/CollisionSystem.h"
#include "SpriteRendererComponent.h"
#include "PhysicsComponent.h"
#include "Projectiles.h"

class Player : public GameObject {
	ColliderComponent collider;
	RigidbodyComponent* physics;
	SpriteSheetAnimationRenderer spriteRenderer;
	SpriteRenderer healthSprite;
	Vector2 frame, acceleration, direction;
	Vector2 startingPosition;
	float maxSpeed;
	float bulletSpeed;
	float hp, maxHp;
	float reloadTime, maxReloadTime; //
	float invicibleTime, maxInvicibleTime;
	double angle;

public:
	void Update() {
		//Collision
		invicibleTime -= Time.deltaTime;
		if (invicibleTime <= 0.0f) {
			invicibleTime = 0;
		}
		if (collider.collisionCol != nullptr) {
			if (invicibleTime <= 0.0f) {
				onDamage(4.0f);
				invicibleTime += maxInvicibleTime;
			}
			Console.Log("Player hitted something");
			collider.collisionCol = nullptr;
		}


		reloadTime -= Time.deltaTime;
		if (reloadTime < 0) {
			reloadTime = 0;
		}
		if (Input.isKeyPressed(SDL_SCANCODE_W)
			|| Input.isKeyPressed(SDL_SCANCODE_UP)) {
			acceleration += direction;
			acceleration = acceleration.Normalize() * 3;
		}

		if (Input.isKeyPressed(SDL_SCANCODE_A)
			|| Input.isKeyPressed(SDL_SCANCODE_LEFT)) {
			angle -= 4.0 * Time.deltaTime;
		}

		if (Input.isKeyPressed(SDL_SCANCODE_D)
			|| Input.isKeyPressed(SDL_SCANCODE_RIGHT)) {
			angle += 4.0 * Time.deltaTime;

		}

		if (Input.isKeyPressed(SDL_SCANCODE_X)) {
			//Player is shooting
			if (reloadTime <= 0) {
				reloadTime += maxReloadTime;
				Shoot();
			}
		}

		else {
			//When player is not shooting
			hp += 3 * Time.deltaTime; //Regenerate 3 hp per second
			if (hp > maxHp) hp = maxHp;
		}
		direction.x = cosf(angle);
		direction.y = sinf(angle);


		//TODO: clean this shit
		int deg = angle * (180.0 / M_PI);
		deg = ((deg - 67) % 180);
		deg = deg < 0 ? deg + 180 : deg;
		if (deg < 45) {
			frame = GridVector(0, 0);
		}
		else if (deg < 90) {
			frame = GridVector(1, 0);
		}
		else if (deg < 135) {
			frame = GridVector(2, 0);
		}
		else {
			frame = GridVector(3, 0);
		}



	}

	void PhysicsUpdate() {
		//add gravity to velocity
		Vector2 moment = acceleration * 10000.0f * Time.fixedDeltaTime;
		moment += (Vector2)gravity * 1300.0f * Time.fixedDeltaTime;
		physics->velocity += moment;
		float speed = clamp<float>(physics->velocity.Magnitude(), 0, maxSpeed);
		physics->velocity = physics->velocity.Normalize() * speed;
		acceleration = acceleration * 0.999f;
		physics->velocity = physics->velocity * 0.997f;
	}
	

	void Init() {

		spriteRenderer.Load("./assets/sprites/plane.bmp", GridVector(4, 1));
		healthSprite.Load("./assets/sprites/health.bmp");
	}

	void Reset() {
		transform.position = startingPosition;
		angle = -M_PI / 2;
		hp = maxHp;
		frame = GridVector(0, 0);
		physics->velocity = Vector2(0, 100);
		direction = Vector2(0, -10);
		acceleration = Vector2(0, -3);

		Vector2 colliderPos = transform.position + collider.offset;
		setColliderPosition(*collider.collider, colliderPos);

	}

	void Render() {
		spriteRenderer.Render(transform.position, frame, angle * radianConst);
		
	}

	void RenderHealth() {
		if (hp < maxHp) {
			healthSprite.RenderScaledCentered(transform.position, hp);
		}
		else {
			healthSprite.RenderScaledCentered(transform.position, 40);

		}
	}

	void onDamage(float value) {
		hp -= value;
	}

	void Shoot() {
		Vector2 position = transform.position + direction * 2;
		Vector2 velocity = physics->velocity + (direction * bulletSpeed);
		//Vector2 direction = velocity.Normalize();
 		int success = playerBullets.Projectile(position, velocity);
	}

	Vector2 getVelocity() {
		return physics->velocity;
	}

	Player() {
		collider.SetCollider(LAYER_PLAYER);
		startingPosition = Vector2(3000, 1000);
		angle = -M_PI/2;
		frame = GridVector(0, 0);
		maxSpeed = 200.0f;
		maxInvicibleTime = 0.3f;
		maxReloadTime = 0.3f;
		hp = maxHp = 10.0f;
		hp = 1.0f;
		bulletSpeed = 250.0f;
		transform.position = startingPosition;

		direction = Vector2(0, -10);
		acceleration = Vector2(0, -3);

		collider.offset = Vector2(12, 12);
		Vector2 position = transform.position + collider.offset;
		Collider col;

		col.circle.x = position.x;
		col.circle.y = position.y;
		col.circle.radius = 12;
		col.circle.flag = CIRCLE_FLAG;
		col.component = &collider;
		*(collider.collider) = col;

		physics = RigidbodyPool.Get(this,&collider);
		physics->useGravity = true;
		
		
	}
	~Player() {
		RigidbodyPool.Return(physics);
	}

};