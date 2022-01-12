#pragma once
#include <SDL.h>
#include "include/Component.h"
#include "TextureManager.h"
#include "libs/Vector2.h"



class Renderer {

};

class SpriteSheetAnimationRenderer : public Component {
	SDL_Texture* spritesheet;
	GridVector frames;
	SDL_Rect frameSize;
public:
	void Render(GridVector position, GridVector frame) {
		frame.x %= frames.x;
		frame.y %= frames.y;
		frameSize.x = frame.x * frameSize.w;
		frameSize.y = frame.y * frameSize.h;
		SDL_RenderCopyEx(ScreenHandleler::getRenderer(), spritesheet, &frameSize,
			new SDL_Rect{ position.x, position.y, frameSize.w,frameSize.h }, NULL, NULL, SDL_FLIP_NONE);
	}
	void Render(GridVector position, GridVector frame, double angle) {
		frame.x %= frames.x;
		frame.y %= frames.y;
		frameSize.x = frame.x * frameSize.w;
		frameSize.y = frame.y * frameSize.h;
		SDL_RenderCopyEx(ScreenHandleler::getRenderer(), spritesheet, &frameSize,
			new SDL_Rect{ position.x, position.y, frameSize.w,frameSize.h }, angle, NULL, SDL_FLIP_NONE);
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
	void Load(texturePath path) {
		sprite = TextureManager.Add(path);
		SDL_QueryTexture(sprite, NULL, NULL, &spriteSize.x, &spriteSize.y);
	}
	void Load(char* path) {
		sprite = TextureManager.Add(path);
		SDL_QueryTexture(sprite, NULL, NULL, &spriteSize.x, &spriteSize.y);
	}
	void Render(GridVector position) {
		SDL_RenderCopy(ScreenHandleler::getRenderer(), sprite, NULL,
			new SDL_Rect{ position.x, position.y, spriteSize.x,spriteSize.y });
	}

	void Render(GridVector position, double angle) {
		SDL_RenderCopyEx(ScreenHandleler::getRenderer(), sprite, NULL,
			new SDL_Rect{ position.x, position.y, spriteSize.x,spriteSize.y },angle,NULL, SDL_FLIP_NONE);
	}
};