#pragma once
#include "include/GameObject.h"
#include "Input.h"
#include "Time.h"
#include "TextRenderer.h"
#include "ColorPalete.h"
#include "include/SDL_Audio.h"
#include "Settings.h"
#include "include/MonoBechaviour.h"

class Menu : public MonoBechaviour {
private:
	bool isOpened;
	TextRenderer renderer;
public:


	void Init(char* font_path) {
		renderer.Load(font_path);
		renderer.SetColor(colors[PRIMARY_COLOR]);
		isOpened = true;
		Time.setTimeScale(0.0f);
	}

	void Awake() override {
		Init("./assets/sprites/font.bmp");
		Show();
	}

	void Update() override{
		if (Input.isKeyJustPressed(SDL_SCANCODE_UP)) {
			Hide();
			Time.setTimeScale(1.0f);
#if !(DISABLE_AUDIO)
			Audio.Resume();
#endif
		}
	}

	void Render() override{
		renderer.RenderCentered("Hetin", GridVector(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 22);
		renderer.RenderCentered("UP - new game", GridVector(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100), 4);
		renderer.RenderCentered("ESC - quit", GridVector(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150), 4);
		renderer.RenderCentered("by tad1", GridVector(SCREEN_WIDTH - 120, SCREEN_HEIGHT - 20), 4);
		renderer.RenderCentered("alpha 2.0", GridVector(150, SCREEN_HEIGHT - 20), 4);
	}

	void Show() {
		isOpened = true;
	}

	void Hide() {
		isOpened = false;
	}

	bool isActive() {
		return isOpened;
	}

};