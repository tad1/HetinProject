#pragma once
#include "SpriteRendererComponent.h"


struct Particle {
	Vector2 position;
	Vector2 velocity;
	int frame;
};

/// <summary>
/// Object pool of particle - 
/// </summary>
template <int SIZE>
class ParticleSystem {

	SpriteSheetAnimationRenderer spritesheet;
	int countOfParticle;
	float framePerSecond; //time for 1 frame
	int frames;


	void Load(char* path; int frames) {
		spritesheet.Load(spritesheet, GridVector(frames, 1));
		frames = frames;
	}

	void Animate() {

	}

	ParticleSystem() {

	}
};