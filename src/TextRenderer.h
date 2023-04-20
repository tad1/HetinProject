#pragma once
#include <SDL.h>
#include "include/Component.h"
#include "TextureManager.h"
#include "include/Vector2.h"




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

	/// <summary>
	/// Loads font
	/// </summary>
	/// <param name="path"></param>
	/// <param name="dimension_"></param>
	void Load(texturePath path, GridVector dimension_ = GridVector(16,16)) {
		letterSpacing = 1;
		font = TextureManager.Add(path);
		dimension = dimension_;
		int width, height;
		SDL_QueryTexture(font, NULL, NULL, &width, &height);
		character.w = width / dimension_.x;
		character.h = height / dimension_.y;
		
	}

	/// <summary>
	/// Loads font
	/// </summary>
	/// <param name="path"></param>
	/// <param name="dimension_"></param>
	void Load(char* path, GridVector dimension_ = GridVector(16, 16)) {
		letterSpacing = 1;
		font = TextureManager.Add(path);
		dimension = dimension_;
		int width, height;
		SDL_QueryTexture(font, NULL, NULL, &width, &height);
		character.w = width / dimension_.x;
		character.h = height / dimension_.y;

	}

	/// <summary>
	/// Set font color
	/// </summary>
	/// <param name="color_"></param>
	void SetColor(SDL_Color color_) {
		color = color_;
	}

	/// <summary>
	/// Render text on screen
	/// </summary>
	/// <param name="text"></param>
	/// <param name="position"></param>
	/// <param name="fontSize"></param>
	void Render(char* text, GridVector position, double fontSize) {
		SDL_Rect letterOutput{
			position.x,
			position.y,
			character.w * fontSize,
			character.h * fontSize
		};

		SDL_SetTextureColorMod(font, color.r, color.g, color.b);
		GridVector offset = GridVector(0,0);
		int c;

		while (*text) {
			c = *text & 255;
			character.x = (c % dimension.x) * character.w;
			character.y = (c / dimension.y) * character.h;

			SDL_RenderCopy(ScreenHandleler::getRenderer(), font, &character, &letterOutput);

			letterOutput.x += letterOutput.w * letterSpacing;
			text++;
		}

	}

	/// <summary>
	/// Render text on screen, where position is center of text
	/// </summary>
	/// <param name="text"></param>
	/// <param name="position"></param>
	/// <param name="fontSize"></param>
	void RenderCentered(char* text, GridVector position, double fontSize) {
		SDL_Rect letterOutput{
			position.x,
			position.y,
			character.w * fontSize,
			character.h * fontSize
		};

		GridVector size;
		size.x = strlen(text) * letterOutput.w;
		size.y = letterOutput.h;

		letterOutput.x -= size.x / 2;
		letterOutput.y -= size.y / 2;

		SDL_SetTextureColorMod(font, color.r, color.g, color.b);
		GridVector offset = GridVector(0, 0);
		int c;

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