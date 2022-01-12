#pragma once
#include "../../HotMemory.h"

class ColliderComponent;

class Layer {
public:
	Collider* colliders;
	bool* inUse;
	int size;

	Collider* Get() {
		for (int i = 0; i < size; i++) {
			if (!inUse[i]) {
				inUse[i] = true;
				return colliders + i;
			}
		}
		return nullptr;
	}

	void Return(Collider* collider) {
		inUse[colliders - collider] = false;
	}

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

			for (int i = 0; i < size; i++) {
				inUse[i] = false;
			}
		}
		
	}

	Layer() {
	}

};

class ColliderManager_ {
	Layer layers[LAYER_COUNT];
	Collider* colliders;
	int size;
public:
	Collider* Get(int layerId) {
		return layers[layerId].Get();
	}

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

	inline bool isAABBColliding(Collider a, Collider b) {
		return (a.rect.x < b.rect.x + b.rect.w &&
			a.rect.x + a.rect.w > b.rect.x &&
			a.rect.y < b.rect.y + b.rect.h &&
			a.rect.y + a.rect.h > b.rect.y);
	}

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

	void checkCollisions(int layerID) {
		HotMemory.Use<ColliderComponent*>();
		Layer& currentLayer = layers[layerID];


		for (int i = 0; i < LAYER_COUNT; i++)
		{
			if (layerInteract(layerID, layersInfo[i].value)) {


				Collider* source, * target;
				source = layers[layerID].colliders;
				target = layers[i].colliders;

				for (int sourceIndex = 0; sourceIndex < layersInfo[layerID].size; sourceIndex++)
					if (layers[layerID].inUse[sourceIndex]) {
						{
							for (int targetIndex = 0; targetIndex < layersInfo[i].size; targetIndex++) {
								if (layers[i].inUse[targetIndex]) {
									//Check collision
									if (isColliding(*source, *target)) {
										HotMemory.Put<ColliderComponent*>(source->component);
										HotMemory.Put<ColliderComponent*>(target->component);
									}
								}
								target++;
							}
							source++;
						}
					}

			}
		}

		ColliderComponent* elements = (ColliderComponent*)HotMemory.elements;
		for (int i = 1; i < HotMemory.count; i += 2) {
			elements[i - 1].OnCollisionEnter(elements[i]);
		}

		HotMemory.Free();

	}

	void draw() {

	}

} ColliderManager;
