#pragma once
#include "include/GameObject.h"
#include "libs/Vector2.h"
#include "Transform.h"
#include "include/ScreenHandleler.h"
#include "Settings.h"
#include "libs/Math.h"

class Camera : public GameObject{
public:
	Vector2 size;
	Transform* target;
	Vector2 targetBorder;


	/// <param name="position"></param>
	/// <returns>position vector in pixels</returns>
	Vector2 WorldToScreenPosition(Vector2 position) {
		return position - transform.position + size;
	}

	void Update() {
		//Follow target
		if (target) {
			transform.position = target->position;
		}
		//Clamp
		transform.position.x = clamp<float>(transform.position.x, size.x, LEVEL_WIDTH - size.x);
		transform.position.y = clamp<float>(transform.position.y, size.y, LEVEL_HEIGHT - size.y);


	}

	/// <summary>
	/// Set camera size and target border in pixels
	/// </summary>
	/// <param name="size_"></param>
	void SetSize(Vector2 size_) {
		size = size_ / 2.0f;
		targetBorder.x = 0.4 * size.x; //target border should be around 1/4 height and width of the screen
		targetBorder.y = 0.5 * size.y;
	}

	Camera() {
		target = nullptr;
	};
};

static Camera mainCamera;

