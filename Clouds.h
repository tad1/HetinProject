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


/// <summary>
/// Selfcaring object pool for clouds, populate clouds, moves them, and render
/// </summary>
class CloudPool : public GenericPool<Cloud, 20> {
	SpriteSheetAnimationRenderer renderer;
	GridVector spriteSize;
	SDL_Color colorMod;
	int useCount;
	float paralaxEffect = 0.9f;
	int typeCount = 9;
	int minHeight = 500; //pixels
	
public:

	/// <summary>
	/// Moves clouds
	/// </summary>
	void Update(){
		for (int i = 0; i < useCount; i++) {
			pool[i].position.x += (float)pool[i].horizontalDirection * Time.deltaTime;
			if (pool[i].position.x > LEVEL_WIDTH) {
				pool[i].position.x -= LEVEL_WIDTH + spriteSize.x;
			}
			else if (pool[i].position.x < -spriteSize.x) {
				pool[i].position.x += LEVEL_WIDTH + spriteSize.x;
			}
		}
	}

	void Render() {
		renderer.Color(colorMod);
		for (int i = 0; i < useCount; i++) {
			renderer.Render(pool[i].position, GridVector(pool[i].type, 0), paralaxEffect);
		}
	}

	/// <summary>
	/// Set paralax effect according to one parameter.
	/// The lower parameter is, the slower background moves
	/// </summary>
	/// <param name="paralaxLevel_"></param>
	void SetParalaxLevel(float paralaxLevel_) {
		paralaxEffect = paralaxLevel_;
	}

	/// <summary>
	/// Set color modulation for all clouds
	/// </summary>
	/// <param name="color"></param>
	void SetColorMod(SDL_Color color) {
		colorMod = color;
	}

	/// <summary>
	/// Loads spritesheet and number of clouds in texture
	/// Spritesheet must have one dimention (x dimension) of frames
	/// </summary>
	/// <param name="path"></param>
	/// <param name="typeCount_"></param>
	void Init(char* path, int typeCount_) {
		colorMod = colors[CLOUD_COLOR];
		typeCount = typeCount_;
		renderer.Load(path, GridVector(typeCount,1));
		spriteSize = renderer.GetSize();
		useCount = 20;
		GridVector position;
		int type;
		int horizontalDirection;
		for (int i = 0; i < useCount; i++) {
			position.y = Random::Number(0, LEVEL_HEIGHT - minHeight);
			position.x = Random::Number(LEVEL_WIDTH);
			type = Random::Number(typeCount);
			horizontalDirection = Random::Number(10, 20);

			pool[i].position = position;
			pool[i].type = type;
			pool[i].horizontalDirection = horizontalDirection;
		}
	}

	CloudPool() {
		useCount = 0;
	}
};