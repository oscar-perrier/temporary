#pragma once
#include "Entity.h"
#include <SDL.h>
#include <SDL_ttf.h>

class Button : public Entity
{
	TTF_Font* Sans = nullptr;
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Texture* Message = nullptr;
	SDL_Rect Message_rect;
public:
	Button(SDL_Renderer* renderer, const char* text, int posX, int posY, int w, int h);

	void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) override;
	Vector2 GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) override;
	void Move(float x, float y) override;

	void Draw(SDL_Renderer* renderer);
};

