#pragma once
#include "include/GameObject.h"
#include "include/Vector2.h"
#include "Transform.h"
#include "include/ScreenHandleler.h"
#include "Settings.h"
#include "include/Math.h"
#include "Time.h"

class Player;

class Camera : public GameObject{
public:
	Vector2 size;
	Player* target;
	Vector2 targetBorder;
	Vector2 lastTargetPosition;


	/// <param name="position"></param>
	/// <returns>position vector in pixels</returns>
	Vector2 WorldToScreenPosition(Vector2 position) {
		return position - transform.position + size;
	}

	void Update();

	/// <summary>
	/// Set camera size and target border in pixels
	/// </summary>
	/// <param name="size_"></param>
	void SetSize(Vector2 size_) {
		size = size_ / 2.0f;
		targetBorder.x = 0.8 * size.x/2; //target border should be around 1/4 height and width of the screen
		targetBorder.y = 0.8 * size.y/2;
	}

	Camera() {
		target = nullptr;
	};
};

static Camera mainCamera;

