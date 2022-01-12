#pragma once
#include "Object.h"
#include "libs/readOnly.h"
#include "Scene.h"
#include "Transform.h"
#include <stdio.h>
#include <string.h>


class GameObject : public Object{
public:
	//readOnly<bool,GameObject> active;
	bool active;
	int layer;
	Scene* scene;
	char tag[20];
	Transform transform;
	

	GameObject(const char* name = "") {
		active = true;
		layer = 0;
		transform.position = Vector2(0, 0);
		transform.scale = Vector2(1, 1);
		//transform.gameObject = this;
		this->name = (char *)name;
	}

	

	bool CompareTag(const char* tag_) {
		return strcmp(tag, tag_) == 0;
	}

	

	static void Destroy(GameObject* obj) {
		/*obj->parent->RemoveChild(obj);
		while (childCount > 0) {
			GameObject::Destroy(GetChild(0));
		}*/

	}
};
