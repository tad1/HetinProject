#pragma once
#include "include/Dictionary.h"
#include "include/ScreenHandleler.h"
#include "include/Copyable.h"
#include <stdio.h>
#include <SDL.h>

/// <summary>
/// Load quered file, remove chroma key (#000000FF black), and converts to texture.
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
SDL_Texture* loadBMPTexture(const char* path);

typedef CopyableString<255> texturePath;

/// <summary>
/// Loads textures, if is not already loaded, and return texture pointer.
/// Destorys textures on delete
/// </summary>
class TextureManager_ {
private:
	Dictionary<texturePath, SDL_Texture*> textures;
public:
	
	
	/// <summary>
	/// Query texture
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	SDL_Texture* Get(texturePath path) {
		return textures[path];
	}


	/// <summary>
	/// Loads texture
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	SDL_Texture* Add(char* path) {
		texturePath tpath = {""};
		tpath = path;
		return Add(tpath);
	}
	/// <summary>
	/// Loads texture
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	SDL_Texture* Add(texturePath path) {
		if (textures.ContainsKey(path)) {
			return textures[path];
		}
		SDL_Texture* texture = loadBMPTexture(path.c_str);
		textures.Add(path, texture);
		return texture;
	}

	/// <summary>
	/// Remove, and destroys texture
	/// </summary>
	/// <param name="path"></param>
	void Remove(texturePath path) {
		SDL_DestroyTexture(textures[path]);
		textures.Remove(path);
	}

	void DeleteAll() {
		for (int i = 0; i < textures.GetCount(); i++) {
			SDL_DestroyTexture(textures.Get(i));
		}
		textures.Clear();
	}

	~TextureManager_() {
		DeleteAll();
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