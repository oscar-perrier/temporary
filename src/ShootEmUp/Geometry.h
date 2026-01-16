#pragma once

#include "CustomMath.h"

struct SDL_Renderer;

struct Color {
	int r;
	int g;
	int b;
};

class Geometry
{
protected:
	float posX;
	float posY;
	int width;
	int height;

	Color color;

public:
	virtual bool Intersects(const Geometry* other) const = 0;
	Geometry(int width, int height);

	virtual void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f);
	virtual void SetPosition(const Vector2& position, float anchorX = 0.5f, float anchorY = 0.5f);
	void Move(float x, float y);

	void SetColor(int r, int g, int b);

	virtual Vector2 GetPosition(float anchorX, float anchorY) const;

	virtual void Resize(int width, int height);

	virtual Vector2 GetSize();

	virtual void Draw(SDL_Renderer* renderer) = 0;
};


