#pragma once

const int CIRCLE_FLAG = 0;

enum ColliderType{CIRCLE,AABB};

typedef float collisionPrecision;

template <class T>
struct Circle {
	T x, y, radius, flag;
};

template <class T>
struct AABB {
	T x, y, w, h;
};

class ColliderComponent;

struct Collider {
	ColliderComponent* component;
	union {
		struct Circle<collisionPrecision> circle;
		struct AABB<collisionPrecision> rect;
	};
};

void setCircleCollider(Collider& collider, collisionPrecision x, collisionPrecision y, collisionPrecision r) {
	collider.circle.x = x;
	collider.circle.y = y;
	collider.circle.radius = r;
	collider.circle.flag = CIRCLE_FLAG;
}

void setRectCollider(Collider& collider, collisionPrecision x, collisionPrecision y, collisionPrecision w, collisionPrecision h) {
	collider.rect.x = x;
	collider.rect.y = y;
	collider.rect.w = w;
	collider.rect.h = h;
}