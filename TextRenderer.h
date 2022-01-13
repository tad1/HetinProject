#pragma once
#include <SDL.h>
#include "include/Component.h"
#include "TextureManager.h"
#include "libs/Vector2.h"




/// <summary>
/// Creates TextRenderer with given font, and color
/// <param name='font'>- font texture</param>
/// <param name='dimension'>- dimension of texture</param>
/// <param name='color'>- color modulation</param>
/// </summary>
class TextRenderer : public Component {
	SDL_Texture* font;
	double letterSpacing;
	GridVector dimension;
	SDL_Rect character;
	SDL_Color color;


public:

	void Load(texturePath path, GridVector dimension_ = GridVector(16,16)) {
		letterSpacing = 1;
		font = TextureManager.Add(path);
		dimension = dimension_;
		int width, height;
		SDL_QueryTexture(font, NULL, NULL, &width, &height);
		character.w = width / dimension_.x;
		character.h = height / dimension_.y;
		
	}

	void Load(char* path, GridVector dimension_ = GridVector(16, 16)) {
		letterSpacing = 1;
		font = TextureManager.Add(path);
		dimension = dimension_;
		int width, height;
		SDL_QueryTexture(font, NULL, NULL, &width, &height);
		character.w = width / dimension_.x;
		character.h = height / dimension_.y;

	}

	void SetColor(SDL_Color color_) {
		color = color_;
	}

	void Render(char* text, GridVector position, double fontSize) {
		SDL_Rect letterOutput{
			position.x,
			position.y,
			character.w * fontSize,
			character.h * fontSize
		};

		GridVector offset = GridVector(0,0);
		int c;
		SDL_SetTextureColorMod(font, color.r, color.g, color.b);

		while (*text) {
			c = *text & 255;
			character.x = (c % dimension.x) * character.w;
			character.y = (c / dimension.y) * character.h;

			SDL_RenderCopy(ScreenHandleler::getRenderer(), font, &character, &letterOutput);

			letterOutput.x += letterOutput.w * letterSpacing;
			text++;
		}

	}
};