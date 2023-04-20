#pragma once
#include "Object.h"
#include "GameObject.h"
#include "../Transform.h"

class GameObject;
class Transform;

/// <summary>
/// A base of all components in game
/// </summary>
class Component : public Object {
public:

	GameObject* gameObject;
	Transform* transform;

	Component() {};
	~Component() {};
};
