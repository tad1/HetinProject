#pragma once
#include <SDL.h>
#include <string.h>


class Input_ {
private:
	Uint8* previousKeyState;
	const Uint8* keyState;
	int keysLenght;
public:
	bool isKeyJustPressed(SDL_Scancode scanCode) {
		return keyState[scanCode] && !previousKeyState[scanCode];
	}
	bool isKeyPressed(SDL_Scancode scanCode) {
		return keyState[scanCode];
	}
	bool isKeyReleased(SDL_Scancode scanCode) {
		return !keyState[scanCode];
	}
	bool isKeyJustReleased(SDL_Scancode scanCode) {
		return !keyState[scanCode] && previousKeyState[scanCode];
	}

	void updatePreviousInput() {

		memcpy(previousKeyState, keyState, keysLenght);

	}

	Input_() {
		keyState = SDL_GetKeyboardState(&keysLenght);
		previousKeyState = new Uint8[keysLenght];
		memcpy(previousKeyState, keyState, keysLenght);
	}

	~Input_() {
		delete[] previousKeyState;
	}

} Input;