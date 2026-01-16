#pragma once

#include "Geometry.h"

#define DEFAULT_PRECISION 30

class Circle : public Geometry
{
	int precision;
public:
	Circle(int radius, int precision = DEFAULT_PRECISION);

	void Draw(SDL_Renderer* renderer) override;

	bool IsColliding(const Circle* target);

	int GetRadius() const { return width / 2; }
};

