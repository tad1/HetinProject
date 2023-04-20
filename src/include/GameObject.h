#pragma once
#include "Object.h"
#include "../Transform.h"
#include <stdio.h>
#include <string.h>

/// <summary>
/// Base of all game objects
/// </summary>
class GameObject : public Object{
public:
	bool active;
	int layer;
	char tag[20];
	Transform transform;
	

	GameObject(const char* name = "") {
		active = true;
		layer = 0;
		transform.position = Vector2(0, 0);
		transform.scale = Vector2(1, 1);
		this->name = (char *)name;
	}


	/// <summary>
	/// Check if tag match
	/// </summary>
	/// <param name="tag_"></param>
	/// <returns>True if tag match</returns>
	bool CompareTag(const char* tag_) {
		return strcmp(tag, tag_) == 0;
	}


	/// <summary>
	/// Not implemented
	/// </summary>
	/// <param name="obj"></param>
	static void Destroy(GameObject* obj) {
		/*obj->parent->RemoveChild(obj);
		while (childCount > 0) {
			GameObject::Destroy(GetChild(0));
		}*/

	}
};
