#pragma once
#include "../libs/Vector2.h"
#include <SDL.h>

class ScreenHandleler {
	static ScreenHandleler* TheScreenHandlerer;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	ScreenHandleler() {};

	SDL_Renderer* IGetRenderer();
	bool IInitialize(const char* windowName, Vector2T<int> size);
	void ISetBackgroundColor(SDL_Color color);
	void IRender();
	GridVector IGetWindowSize();

public:
	ScreenHandleler(const ScreenHandleler&) = delete;

	static ScreenHandleler& Get() {
		static ScreenHandleler instance;
		return instance;
	}

	static SDL_Renderer* getRenderer() { return Get().IGetRenderer(); };
	static bool Initialize(const char* windowName, Vector2T<int> size) {return Get().IInitialize(windowName, size); };
	static void SetBackgroundColor(SDL_Color color) { Get().ISetBackgroundColor(color); };
	static Vector2 GetWindowSize() { return Get().IGetWindowSize(); }
	static void Render() { Get().IRender(); };

	~ScreenHandleler();

};