#include "Circle.h"

#include <SDL.h>

#include "CustomMath.h"

Circle::Circle(int radius, int prec) : Geometry(radius * 2, radius * 2)
{
	precision = prec;
}

void Circle::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,255);
	float anglePerPoint = (2.0f * M_PI) / precision;

	float radius = GetRadius();

	Vector2 center = GetPosition(0.5f, 0.5f);

	int prevX = radius * cos(0) + center.x;
	int prevY = radius * sin(0) + center.y;

	for (int i = 1; i <= precision; i++) {
		int newX = radius * cos(anglePerPoint * i) + center.x;
		int newY = radius * sin(anglePerPoint * i) + center.y;
		SDL_RenderDrawLine(renderer, prevX, prevY, newX, newY);
		prevX = newX;
		prevY = newY;
	}
}

bool Circle::IsColliding(const Circle* target) {
	Vector2 center1 = GetPosition(0.5f, 0.5f);
	Vector2 center2 = target->GetPosition(0.5f, 0.5f);

	float distance = CustomMath::GetDistance(center1.x, center1.y, center2.x, center2.y);
	float radiusDist = GetRadius() + target->GetRadius();

	return distance <= radiusDist;
}