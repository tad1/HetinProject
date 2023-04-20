#pragma once
#include "include/Vector2.h"
#include "vector.h"
#include "include/Component.h"

#include "include/GameObject.h"
#include <assert.h>

class GameObject;

/// <summary>
/// Allow to track GameObject position, and scale
/// </summary>
class Transform{
public:
	/// <summary>
	/// Relative position to parent
	/// </summary>
	Vector2 position;
	Vector2 scale;

	Transform* parent;

	Vector<Transform*> children;
	int childCount;

	/// <summary>
	/// Moves position
	/// </summary>
	/// <param name="translation"></param>
	void Translate(Vector2 translation) {
		position += translation;
	}

	/// <summary>
	/// Get world position
	/// </summary>
	/// <returns></returns>
	Vector2 WorldPosition() {
		if (parent != nullptr) {
			return parent->WorldPosition() + position;
		}
		return position;
	}

	void SetParent(Transform& obj) {
		assert(obj.parent == nullptr);
		obj.children.push_back(this);
		obj.childCount++;
		this->parent = &obj;
	}

	void RemoveChild(Transform& obj) {
		assert(children.find(&obj) != -1);
		children.remove(&obj);
		childCount--;
	}

	Transform& GetChild(int index) {
		return *children[index];
	}

	Transform() {
		parent = nullptr;
	}
};