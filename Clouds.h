#pragma once
#include "include/GenericPool.h"
#include "libs/Vector2.h"
#include "SpriteRendererComponent.h"
#include "libs/Random.h"
#include "Settings.h"
#include "ColorPalete.h"

class Cloud {
public:
	Vector2 position;
	int type;
	int horizontalDirection;
};

class CloudPool : public GenericPool<Cloud, 20> {
	SpriteSheetAnimationRenderer renderer;
	SDL_Color colorMod;
	int useCount;
	float paralaxEffect = 0.9f;
	int typeCount = 9;
	int minHeight = 500; //pixels
	
public:
	void Update(){
		for (int i = 0; i < useCount; i++) {
			pool[i].position.x += pool[i].horizontalDirection * Time.deltaTime;
		}
	}

	void Render() {
		renderer.Color(colorMod);
		for (int i = 0; i < useCount; i++) {
			renderer.Render(pool[i].position, GridVector(pool[i].type, 0), paralaxEffect);
		}
	}

	void SetParalaxLevel(float paralaxLevel_) {
		paralaxEffect = paralaxLevel_;
	}

	void SetColorMod(SDL_Color color) {
		colorMod = color;
	}

	void Init(char* path, int typeCount_) {
		colorMod = colors[CLOUD_COLOR];
		typeCount = typeCount_;
		renderer.Load(path, GridVector(typeCount,1));
		useCount = 20;
		GridVector position;
		int type;
		int horizontalDirection;
		for (int i = 0; i < useCount; i++) {
			position.y = Random::Number(0, LEVEL_HEIGHT - minHeight);
			position.x = Random::Number(LEVEL_WIDTH);
			type = Random::Number(typeCount);
			horizontalDirection = Random::Number(20, 50);

			pool[i].position = position;
			pool[i].type = type;
		}
	}

	CloudPool() {
		useCount = 0;
	}
};