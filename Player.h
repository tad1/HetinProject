#pragma once
#include "include/GameObject.h"
#include "include/CollisionSystem.h"
#include "SpriteRendererComponent.h"
#include "PhysicsComponent.h"
#include "Projectiles.h"
#include "Score.h"

/// <summary>
/// Playable character
/// </summary>
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

	float reloadTime, maxReloadTime;
	float invicibleTime, maxInvicibleTime;
	double angle;

public:
	void Update() {
		invicibleTime -= Time.deltaTime;
		if (invicibleTime <= 0.0f) {
			invicibleTime = 0;
		}
		//Collision check
		if (collider.collisionCol != nullptr) {
			if (invicibleTime <= 0.0f) {
				onDamage(4.0f);
				mainScore.removeScore(5);
				invicibleTime += maxInvicibleTime;
			}
			collider.collisionCol = nullptr;
		}

		//Check if player is outsite level
		if (transform.position.x < 0 || transform.position.x > LEVEL_WIDTH
			|| transform.position.y < 0 || transform.position.y > LEVEL_HEIGHT - SEA_LEVEL) {
			hp -= 5 * Time.deltaTime;
		}

		reloadTime -= Time.deltaTime;
		if (reloadTime < 0) {
			reloadTime = 0;
		}

		//Move handle
		if (Input.isKeyPressed(SDL_SCANCODE_W)
			|| Input.isKeyPressed(SDL_SCANCODE_UP)) {
			acceleration += direction;
			acceleration = acceleration.Normalize() * 3;
		}

		//Rotation handle
		if (Input.isKeyPressed(SDL_SCANCODE_A)
			|| Input.isKeyPressed(SDL_SCANCODE_LEFT)) {
			angle -= 4.0 * Time.deltaTime;
		}

		//Rotation handle
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
		} else {
			//When player is not shooting
			hp += 3 * Time.deltaTime; //Regenerate 3 hp per second
			if (hp > maxHp) hp = maxHp;
		}
		direction.x = cosf(angle);
		direction.y = sinf(angle);


		//convert radians to degrees
		int deg = angle * radianConst;

		//shift degrees to match animation
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
		Vector2 moment = acceleration * 10000.0f * Time.fixedDeltaTime;
		//add gravity to velocity
		moment += (Vector2)gravity * 1300.0f * Time.fixedDeltaTime;
		physics->velocity += moment;

		float speed = clamp<float>(physics->velocity.Magnitude(), 0, maxSpeed);
		physics->velocity = physics->velocity.Normalize() * speed;

		acceleration = acceleration * 0.997f; //decrease acceleration by friction
		physics->velocity = physics->velocity * 0.997f; //decrease velocity by friction
	}
	

	void Init() {

		spriteRenderer.Load("./assets/sprites/plane.bmp", GridVector(4, 1)); //4 frames of animation
		healthSprite.Load("./assets/sprites/health.bmp");
	}

	void Reset() {
		transform.position = startingPosition;
		angle = -M_PI / 2; //-90 deg in radians
		hp = maxHp;
		frame = GridVector(0, 0);
		physics->velocity = Vector2(0, 100); //starting velocity
		direction = Vector2(0, -10); //up
		acceleration = Vector2(0, -3); //up

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
			healthSprite.RenderScaledCentered(transform.position, 100); //100 - Just a big number to fill screen
		}
	}

	void onDamage(float value) {
		hp -= value;
	}

	void Shoot() {
		Vector2 position = transform.position + direction * 2;
		Vector2 velocity = physics->velocity + (direction * bulletSpeed);
 		int success = playerBullets.Projectile(position, velocity);
	}

	Vector2 getVelocity() {
		return physics->velocity;
	}

	Player() {
		collider.SetCollider(LAYER_PLAYER);
		startingPosition = Vector2(3000, 1800);
		angle = -M_PI/2; //-90 deg in radians
		frame = GridVector(0, 0); //starting frame
		maxSpeed = 200.0f; //px per second
		maxInvicibleTime = 0.3f; //seconds
		maxReloadTime = 0.3f; //seconds
		hp = maxHp = 10.0f; //hit point
		bulletSpeed = 300.0f; //px per second
		transform.position = startingPosition;

		direction = Vector2(0, -10); //px per second
		acceleration = Vector2(0, -3); //px per second^2

		collider.offset = Vector2(12, 12); //hardcoded collider offset - px
		Vector2 position = transform.position + collider.offset;
		Collider col;

		col.circle.x = position.x;
		col.circle.y = position.y;
		col.circle.radius = 12; //hardcoded collider radius - px
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