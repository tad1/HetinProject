#pragma once
#include "libs/Vector2.h"
#include "libs/readOnly.h"
#include "vector.h"
#include "include/Component.h"

#include "include/GameObject.h"
#include <assert.h>

class GameObject;

class Transform{ //: public Component{
public:
	Vector2 position;
	Vector2 scale;

	Transform* parent;

	Vector<Transform*> children;
	int childCount;

	void Translate(Vector2 translation) {
		position += translation;
		//for each children update position
	}

	Vector2 WorldPosition() {
		if (parent != nullptr) {
			return parent->WorldPosition() + position;
		}
		return position;
	}

	void SetParent(Transform& obj) {
		assert(obj.parent != nullptr);
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