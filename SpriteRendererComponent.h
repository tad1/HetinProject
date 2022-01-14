#pragma once
#include <SDL.h>
#include "include/Component.h"
#include "TextureManager.h"
#include "libs/Vector2.h"
#include "Camera.h"

class SpriteSheetAnimationRenderer : public Component {
	SDL_Texture* spritesheet;
	GridVector frames;
	SDL_Rect frameSize;
public:
	void Color(SDL_Color color) {
		SDL_SetTextureColorMod(spritesheet, color.r, color.g, color.b);
		SDL_SetTextureAlphaMod(spritesheet, color.a);
	}
	void Render(GridVector position, GridVector frame, float paralaxLevel = 1.0f) {
		GridVector renderPosition = mainCamera.WorldToScreenPosition(position);
		renderPosition = renderPosition * paralaxLevel;
		frame.x %= frames.x;
		frame.y %= frames.y;
		frameSize.x = frame.x * frameSize.w;
		frameSize.y = frame.y * frameSize.h;
		SDL_RenderCopyEx(ScreenHandleler::getRenderer(), spritesheet, &frameSize,
			new SDL_Rect{ renderPosition.x, renderPosition.y, frameSize.w,frameSize.h }, NULL, NULL, SDL_FLIP_NONE);
	}
	void Render(GridVector position, GridVector frame, double angle, float paralaxLevel = 1.0f) {
		GridVector renderPosition = mainCamera.WorldToScreenPosition(position);
		frame.x %= frames.x;
		frame.y %= frames.y;
		frameSize.x = frame.x * frameSize.w;
		frameSize.y = frame.y * frameSize.h;
		SDL_RenderCopyEx(ScreenHandleler::getRenderer(), spritesheet, &frameSize,
			new SDL_Rect{ renderPosition.x, renderPosition.y, frameSize.w,frameSize.h }, angle, NULL, SDL_FLIP_NONE);
	}
	void Load(texturePath path, GridVector frames_) {
		frames = frames_;
		spritesheet = TextureManager.Add(path);
		GridVector spriteSize;
		SDL_QueryTexture(spritesheet, NULL, NULL, &spriteSize.x, &spriteSize.y);
		frameSize.w = spriteSize.x / frames.x;
		frameSize.h = spriteSize.y / frames.y;
		
	}
	void Load(char* path, GridVector frames_) {
		frames = frames_;
		spritesheet = TextureManager.Add(path);
		GridVector spriteSize;
		SDL_QueryTexture(spritesheet, NULL, NULL, &spriteSize.x, &spriteSize.y);
		frameSize.w = spriteSize.x / frames.x;
		frameSize.h = spriteSize.y / frames.y;
	}
};

class SpriteRenderer : public Component{
	SDL_Texture* sprite;
	GridVector spriteSize;

public:
	//TODO: make one funciton call other
	void Load(texturePath path) {
		sprite = TextureManager.Add(path);
		SDL_QueryTexture(sprite, NULL, NULL, &spriteSize.x, &spriteSize.y);
	}
	void Load(char* path) {
		sprite = TextureManager.Add(path);
		SDL_QueryTexture(sprite, NULL, NULL, &spriteSize.x, &spriteSize.y);
	}
	void Render(GridVector position) {
		GridVector renderPosition = mainCamera.WorldToScreenPosition(position);
		SDL_RenderCopy(ScreenHandleler::getRenderer(), sprite, NULL,
			new SDL_Rect{ renderPosition.x, renderPosition.y, spriteSize.x,spriteSize.y });
	}

	void Render(GridVector position, double angle) {
		GridVector renderPosition = mainCamera.WorldToScreenPosition(position);
		SDL_RenderCopyEx(ScreenHandleler::getRenderer(), sprite, NULL,
			new SDL_Rect{ renderPosition.x, renderPosition.y, spriteSize.x,spriteSize.y },angle,NULL, SDL_FLIP_NONE);
	}
};