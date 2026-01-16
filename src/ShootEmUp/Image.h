#pragma once

#include "Geometry.h"

struct SDL_Texture;
struct SDL_Rect;

class Image : public Geometry
{
	SDL_Texture* texture;
	SDL_Rect* srcRect;
	Vector2 drawSize;
	int rotation;

public:
	Image(SDL_Renderer* renderer, const char* path, int rotation = 0, int spritePosX = -1, int spritePosY = -1, int spriteWidth = -1, int spriteHeight = -1);

	void Resize(int width, int height) override;
	bool Intersects(const Geometry* other) const override;

	void Draw(SDL_Renderer* renderer) override;

	Vector2 GetSize() override;

	Vector2 GetPosition(float anchorX, float anchorY) const override;

	void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) override;
	void SetPosition(const Vector2& position, float anchorX = 0.5f, float anchorY = 0.5f) override;
};


