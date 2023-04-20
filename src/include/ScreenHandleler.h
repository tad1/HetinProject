#pragma once
#include "../include/Vector2.h"
#include <SDL.h>

/// <summary>
/// Singleton API to handle screen, and renderer requests
/// </summary>
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

	//Disallow to copy singleton
	ScreenHandleler(const ScreenHandleler&) = delete;

	/// <summary>
	/// Return instance of Singleton
	/// </summary>
	static ScreenHandleler& Get() {
		static ScreenHandleler instance;
		return instance;
	}
	

	/// <summary>
	/// Returns main renderer
	/// </summary>
	static SDL_Renderer* getRenderer() { return Get().IGetRenderer(); };
	
	/// <summary>
	///  Initalize SDL, creates window, and renderer
	/// </summary>
	static bool Initialize(const char* windowName, Vector2T<int> size) {return Get().IInitialize(windowName, size); };
	
	/// <summary>
	/// Set screen background color
	/// </summary>
	static void SetBackgroundColor(SDL_Color color) { Get().ISetBackgroundColor(color); };
	
	/// <summary>
	/// Returns windows size in pixels
	/// </summary>
	static Vector2 GetWindowSize() { return Get().IGetWindowSize(); }
	
	/// <summary>
	/// Render textures from buffer to screen, and clear render buffer
	/// </summary>
	static void Render() { Get().IRender(); };

	~ScreenHandleler();

};
