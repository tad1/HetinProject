#pragma once
#include "SpriteRendererComponent.h"
#include "Time.h"

struct Particle {
	Vector2 position;
	Vector2 velocity;
	int frame;
	float frameTimer;
};

/// <summary>
/// Object pool of particles
/// </summary>
template <int SIZE>
class ParticleSystem {

	Particle particles[SIZE];
	bool inUse[SIZE];
	bool renderOnScreen;
	SpriteSheetAnimationRenderer spritesheet;
	float secondsPerFrame; //time for 1 frame
	float frameTimer;
	int frames;

public:
	void Load(char* path, int frames_) {
		spritesheet.Load(path, GridVector(frames_, 1));
		frames = frames_;
	}

	/// <summary>
	/// Update particles animaiton frames and render
	/// </summary>
	void Animate() {
		Particle* currentParticle;
		for (int i = 0; i < SIZE; i++) {
			if (inUse[i]) {
				currentParticle = &particles[i];
				currentParticle->frameTimer -= Time.deltaTime;
				currentParticle->position += currentParticle->velocity * Time.deltaTime;

				if (currentParticle->frameTimer <= 0) {
					currentParticle->frameTimer += secondsPerFrame;
					currentParticle->frame++;
					if (currentParticle->frame >= frames) {
						inUse[i] = false;
					}

				}
				if (renderOnScreen) {
					spritesheet.RenderOnScreen(currentParticle->position, GridVector(currentParticle->frame, 0));
				}
				else {
					spritesheet.Render(currentParticle->position, GridVector(currentParticle->frame, 0));
				}
			}
		}
	}

	void Create(Vector2 position, Vector2 velocity) {
		for (int i = 0; i < SIZE; i++) {
			if (!inUse[i]) {
				inUse[i] = true;
				particles[i].position = position;
				particles[i].velocity = velocity;
				particles[i].frame = 0;
				particles[i].frameTimer = secondsPerFrame;
				return;
			}
		}
	}

	void RenderOnScreen() {
		renderOnScreen = true;
	}

	ParticleSystem() {
		frameTimer = secondsPerFrame = 0.1f;
		for (int i = 0; i < SIZE; i++) {
			inUse[i] = false;
		}
		renderOnScreen = false;
	}
};


static ParticleSystem<40> explosions;