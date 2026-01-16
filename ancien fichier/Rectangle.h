#pragma once

#include "Geometry.h"

class Rectangle : public Geometry
{
public:
	Rectangle(int w, int h);

	bool Intersects(const Geometry* other) const override;

	void Draw(SDL_Renderer* renderer) override;

	//SDL_bool SDL_IntersectRect(const SDL_Rect* A, const SDL_Rect* B, SDL_Rect* result) {}
};


