#pragma once
#include "../../HotMemory.h"
#include "SDL.h"
#include "../ScreenHandleler.h"
#include "../../ColorPalete.h"


class ColliderComponent;

/// <summary>
/// Pool of colliders from one layer
/// </summary>
class Layer {
public:
	Collider* colliders;
	bool* inUse;
	int size;
	bool ownMemory;

	/// <summary>
	/// Query pool for free collider
	/// </summary>
	/// <returns>nullptr if none collider is avaiable</returns>
	Collider* Get() {
		for (int i = 0; i < size; i++) {
			if (!inUse[i]) {
				inUse[i] = true;
				return colliders + i;
			}
		}
		return nullptr;
	}

	/// <summary>
	/// Return collider to pool
	/// </summary>
	/// <param name="collider"></param>
	void Return(Collider* collider) {
		inUse[collider - colliders] = false;
	}

	/// <summary>
	/// Creates pool, with selected size
	/// </summary>
	/// <param name="size_"></param>
	/// <param name="location"></param>
	void Init(int size_, Collider* location = nullptr) {
		size = size_;
		if (location != nullptr) {
			colliders = location;
			inUse = new bool[size];

			for (int i = 0; i < size; i++) {
				inUse[i] = false;
			}
		}
		else {
			colliders = new Collider[size];
			inUse = new bool[size];
			ownMemory = true;

			for (int i = 0; i < size; i++) {
				inUse[i] = false;
			}
		}
		
	}

	void Draw() {
		for (int i = 0; i < size; i++) {
			if (inUse[i]) {
				GridVector startingPoint;
				startingPoint.x = colliders[i].circle.x;
				startingPoint.y = colliders[i].circle.y;
				startingPoint = mainCamera.WorldToScreenPosition(startingPoint);
				SDL_Point points[5];
				//Circle
				if (colliders[i].circle.flag == CIRCLE_FLAG) {
					points[0].x = startingPoint.x;
					points[0].y = startingPoint.y - colliders[i].circle.radius;

					points[1].x = startingPoint.x + colliders[i].circle.radius;
					points[1].y = startingPoint.y;

					points[2].x = startingPoint.x;
					points[2].y = startingPoint.y + colliders[i].circle.radius;

					points[3].x = startingPoint.x - colliders[i].circle.radius;
					points[3].y = startingPoint.y;

					points[4] = points[0];

				}
				else {
					//Rect
					points[0].x = startingPoint.x;
					points[0].y = startingPoint.y;

					points[1].x = startingPoint.x + colliders[i].rect.w;
					points[1].y = startingPoint.y;

					points[2].x = startingPoint.x + colliders[i].rect.w;
					points[2].y = startingPoint.y + colliders[i].rect.h;

					points[3].x = startingPoint.x;
					points[3].y = startingPoint.y + colliders[i].rect.h;

					points[4] = points[0];
				}
				SDL_RenderDrawLines(ScreenHandleler::getRenderer(), points, 5);
			}
		}
	}

	Layer() {
		ownMemory = false;
	}

	~Layer() {
		delete[] inUse;
		if (ownMemory) {
			delete[] colliders;
		}
	}

};

class ColliderManager_ {
	Layer layers[LAYER_COUNT];
	Collider* colliders;
	int size;
public:

	/// <summary>
	/// Query Manager for free collider for given layer
	/// </summary>
	/// <param name="layerId"></param>
	/// <returns>Pointer to collider on succes, otherwise nullptr</returns>
	Collider* Get(int layerId) {
		return layers[layerId].Get();
	}

	/// <summary>
	/// Return collider to pool in given layer
	/// </summary>
	/// <param name="collider"></param>
	/// <param name="layerID"></param>
	void Return(Collider* collider, int layerID) {
		layers[layerID].Return(collider);
	}

	ColliderManager_() {
		size = 0;
		int offset = 0;
		for (int i = 0; i < LAYER_COUNT; i++)
		{
			size += layersInfo[i].size;
		}
		colliders = new Collider[size];
		for (int i = 0; i < LAYER_COUNT; i++)
		{
			layers[i].Init(layersInfo[i].size, colliders + offset);
			offset += layersInfo[i].size;
		}
	}

	~ColliderManager_() {
		delete[] colliders;
	}


	/// <returns>true on collision</returns>
	inline bool isAABBColliding(Collider a, Collider b) {
		return (a.rect.x < b.rect.x + b.rect.w &&
			a.rect.x + a.rect.w > b.rect.x &&
			a.rect.y < b.rect.y + b.rect.h &&
			a.rect.y + a.rect.h > b.rect.y);
	}

	/// <returns>true on colliison</returns>
	inline bool isAABBvsCircleColliding(Collider a, Collider b) {
		
		collisionPrecision clampedX = b.circle.x < a.rect.x ? a.rect.x : (b.circle.x < a.rect.x + a.rect.w ? b.circle.x : a.rect.x + a.rect.w);
		collisionPrecision clampedY = b.circle.y < a.rect.y ? a.rect.y : (b.circle.y < a.rect.y + a.rect.h ? b.circle.y : a.rect.y + a.rect.h);

		if ((clampedX != a.rect.x && clampedX != a.rect.x + a.rect.w)
			|| (clampedY != a.rect.y && clampedY != a.rect.y + a.rect.h)) {
			return true;
		}
		collisionPrecision x = b.circle.x - clampedX;
		collisionPrecision y = b.circle.y - clampedY;
		collisionPrecision d = x * x + y * y;
		collisionPrecision r = b.circle.radius * b.circle.radius;
		return d < r;
	}

	/// <summary>
	/// Test collision for colliders in any type [AABB (rect), and circle]
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>true on collision</returns>
	inline bool isColliding(Collider a, Collider b) {
		
		if (a.circle.flag == CIRCLE_FLAG) {
			if (b.circle.flag == CIRCLE_FLAG) {
				//CvC
				collisionPrecision r = a.circle.radius + b.circle.radius;
				r *= r;
				collisionPrecision x = (a.circle.x - b.circle.x);
				collisionPrecision y = (a.circle.y - b.circle.y);
				collisionPrecision d = (x * x) + (y * y);
				return r > d;
			}
			//CvAABB
			return isAABBvsCircleColliding(b, a);
		}
		else if (b.circle.flag == CIRCLE_FLAG) {
			//CvsAABB
			return isAABBvsCircleColliding(a, b);
		}
		else {
			//Rect vs Rect
			return isAABBColliding(a, b);
		}
		
	}

	/// <summary>
	/// Check collisions for all layers
	/// </summary>
	void checkAllCollisions() {
		for (int i = 0; i < LAYER_COUNT; i++) {
			checkCollisions(i);
		}
	}

	/// <summary>
	/// Check collision for colliders in given layer
	/// </summary>
	/// <param name="layerID"></param>
	void checkCollisions(int layerID) {
		HotMemory.Use<ColliderComponent*>();
		Layer& currentLayer = layers[layerID];


		for (int i = 0; i < LAYER_COUNT; i++)
		{
			if (layerInteract(layerID, layersInfo[i].value)) {
				//Given layer interact with this layer
				//Checking collisions

				Collider* source, * target;
				

				for (int sourceIndex = 0; sourceIndex < layersInfo[layerID].size; sourceIndex++)
					if (layers[layerID].inUse[sourceIndex]) {
						{	
							source = &layers[layerID].colliders[sourceIndex];
							//Test each to each collision
							//Not optimalised but it does its work
							for (int targetIndex = 0; targetIndex < layersInfo[i].size; targetIndex++) {
								target = &layers[i].colliders[targetIndex];
								if (layers[i].inUse[targetIndex]) {
									//Check collision
									if (isColliding(*source, *target)) {
										//Put collider components to buffer
										HotMemory.Put<ColliderComponent*>(source->component);
										HotMemory.Put<ColliderComponent*>(target->component);
									}
								}
							}
						}
					}

			}
		}

		//trigger collision event on source colliders
		ColliderComponent** elements = (ColliderComponent**)HotMemory.elements;
		for (int i = 1; i < HotMemory.count; i += 2) {
			elements[i - 1]->OnCollisionEnter(elements[i]);
		}

		HotMemory.Free();

	}

	/// <summary>
	/// Draws all colliders in red
	/// </summary>
	void Draw() {
		SDL_SetRenderDrawColor(ScreenHandleler::getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
		for (int i = 0; i < LAYER_COUNT; i++) {
			layers[i].Draw();
		}
		ScreenHandleler::SetBackgroundColor(colors[HEALTH_COLOR]);
	}

};
static ColliderManager_ ColliderManager;
