#pragma once
#include <SDL.h>
#include "include/Component.h"
#include "TextureManager.h"
#include "libs/Vector2.h"
#include "Camera.h"

/// <summary>
/// Draws spritesheet animation on screen
/// </summary>
class SpriteSheetAnimationRenderer : public Component {
	SDL_Texture* spritesheet;
	GridVector frames;
	SDL_Rect frameSize;
public:
	/// <summary>
	/// Set color modulation
	/// </summary>
	/// <param name="color"></param>
	void Color(SDL_Color color) {
		SDL_SetTextureColorMod(spritesheet, color.r, color.g, color.b);
		SDL_SetTextureAlphaMod(spritesheet, color.a);
	}

	/// <summary>
	/// Render sprite in world
	/// </summary>
	/// <param name="position"></param>
	/// <param name="frame"></param>
	/// <param name="paralaxLevel">- the lower it is the slower it moves</param>
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

	/// <summary>
	/// Render rotated sprite in world
	/// </summary>
	/// <param name="position"></param>
	/// <param name="frame"></param>
	/// <param name="angle">- degrees</param>
	/// <param name="paralaxLevel">- the lower it is the slower sprite moves</param>
	void Render(GridVector position, GridVector frame, double angle, float paralaxLevel = 1.0f) {
		GridVector renderPosition = mainCamera.WorldToScreenPosition(position);
		frame.x %= frames.x;
		frame.y %= frames.y;
		frameSize.x = frame.x * frameSize.w;
		frameSize.y = frame.y * frameSize.h;
		SDL_RenderCopyEx(ScreenHandleler::getRenderer(), spritesheet, &frameSize,
			new SDL_Rect{ renderPosition.x, renderPosition.y, frameSize.w,frameSize.h }, angle, NULL, SDL_FLIP_NONE);
	}

	/// <summary>
	/// Loads spritesheet as texture
	/// </summary>
	/// <param name="path"></param>
	/// <param name="frames_">- number of frames in 2 dimensions</param>
	void Load(texturePath path, GridVector frames_) {
		frames = frames_;
		spritesheet = TextureManager.Add(path);
		GridVector spriteSize;
		SDL_QueryTexture(spritesheet, NULL, NULL, &spriteSize.x, &spriteSize.y);
		frameSize.w = spriteSize.x / frames.x;
		frameSize.h = spriteSize.y / frames.y;
		
	}

	/// <summary>
	/// Loads spritesheet as texture
	/// </summary>
	/// <param name="path"></param>
	/// <param name="frames_">- number of frames in 2 dimensions</param>
	void Load(char* path, GridVector frames_) {
		texturePath tpath = { "" };
		tpath = path;
		Load(tpath, frames_);
	}

	/// <summary>
	/// Return spritesheet size in pixels
	/// </summary>
	/// <returns></returns>
	GridVector GetSize() {
		GridVector result;
		result.x = frameSize.w;
		result.y = frameSize.h;
		return result;
	}
};

class SpriteRenderer : public Component{
	SDL_Texture* sprite;
	GridVector spriteSize;

public:
	/// <summary>
	/// Set color modulation
	/// </summary>
	/// <param name="color"></param>
	void Color(SDL_Color color_) {
		SDL_SetTextureColorMod(sprite, color_.r, color_.g, color_.b);
		SDL_SetTextureAlphaMod(sprite, color_.a);
	}

	/// <summary>
	/// Loads sprite as texture
	/// </summary>
	/// <param name="path"></param>
	void Load(texturePath path) {
		sprite = TextureManager.Add(path);
		SDL_QueryTexture(sprite, NULL, NULL, &spriteSize.x, &spriteSize.y);
	}

	/// <summary>
	/// Loads sprite as texture
	/// </summary>
	/// <param name="path"></param>
	void Load(char* path) {
		texturePath tpath = { "" };
		tpath = path;
		Load(tpath);
	}

	/// <summary>
	/// Render texture in world
	/// </summary>
	/// <param name="position"></param>
	void Render(GridVector position) {
		GridVector renderPosition = mainCamera.WorldToScreenPosition(position);
		SDL_RenderCopy(ScreenHandleler::getRenderer(), sprite, NULL,
			new SDL_Rect{ renderPosition.x, renderPosition.y, spriteSize.x,spriteSize.y });
	}


	/// <summary>
	/// Render scaled centered texture in world
	/// </summary>
	/// <param name="position"></param>
	/// <param name="scale"></param>
	void RenderScaledCentered(GridVector position, float scale) {
		GridVector renderPosition = mainCamera.WorldToScreenPosition(position);
		GridVector outputSize = spriteSize * scale;
		renderPosition -= outputSize / 2;
		SDL_RenderCopy(ScreenHandleler::getRenderer(), sprite, NULL,
			new SDL_Rect{ renderPosition.x, renderPosition.y, outputSize.x,outputSize.y });
	}

	/// <summary>
	/// Render Scaled texture in world
	/// </summary>
	/// <param name="position"></param>
	/// <param name="scale"></param>
	void RenderScaled(GridVector position, GridVector scale) {
		GridVector renderPosition = mainCamera.WorldToScreenPosition(position);
		GridVector outputSize = spriteSize * scale;
		SDL_RenderCopy(ScreenHandleler::getRenderer(), sprite, NULL,
			new SDL_Rect{ renderPosition.x, renderPosition.y, outputSize.x,outputSize.y });
	}

	/// <summary>
	/// Render rotated texture in world
	/// </summary>
	/// <param name="position"></param>
	/// <param name="angle"> - degrees</param>
	void Render(GridVector position, double angle) {
		GridVector renderPosition = mainCamera.WorldToScreenPosition(position);
		SDL_RenderCopyEx(ScreenHandleler::getRenderer(), sprite, NULL,
			new SDL_Rect{ renderPosition.x, renderPosition.y, spriteSize.x,spriteSize.y },angle,NULL, SDL_FLIP_NONE);
	}
};