#pragma once
#include "libs/Dictionary.h"
#include "include/ScreenHandleler.h"
#include "libs/Copyable.h"
#include <stdio.h>
#include <SDL.h>


SDL_Texture* loadBMPTexture(const char* path);

typedef CopyableString<30> texturePath;

class TextureManager_ {
private:
	Dictionary<texturePath, SDL_Texture*> textures;
public:
	SDL_Texture* Get(texturePath path) {
		return textures[path];
	}

	SDL_Texture* Add(char* path) {
		texturePath tpath = {""};
		tpath = path;
		return Add(tpath);
	}

	SDL_Texture* Add(texturePath path) {
		if (textures.ContainsKey(path)) {
			return textures[path];
		}
		SDL_Texture* texture = loadBMPTexture(path.c_str);
		textures.Add(path, texture);
		return texture;
	}
	void Remove(texturePath path) {
		textures.Remove(path);
	}
	~TextureManager_() {
		for (int i = 0; i < textures.GetCount(); i++) {
			SDL_DestroyTexture(textures.Get(i));
		}
	}
} TextureManager;


SDL_Texture* loadBMPTexture(const char* path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == NULL) {
		printf("Load BMP Error at %s: %s\n", path, SDL_GetError());
		return NULL;
	}

	SDL_SetColorKey(loadedSurface, SDL_TRUE, 0x000000);

	newTexture = SDL_CreateTextureFromSurface(ScreenHandleler::getRenderer(), loadedSurface);
	if (newTexture == NULL) {
		printf("Load BMP Error: %s\n", SDL_GetError());
	}
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}