#include "Geometry.h"

Geometry::Geometry(int w, int h)
{
	posX = 0;
	posY = 0;
	width = w;
	height = h;
	color = { 255,255,0 };
}


void Geometry::SetPosition(float x, float y, float anchorX, float anchorY)
{
	posX = x - width * anchorX;
	posY = y - height * anchorY;
}

void Geometry::SetPosition(const Vector2& position, float anchorX, float anchorY)
{
	SetPosition(position.x, position.y, anchorX, anchorY);
}

void Geometry::Move(float x, float y)
{
	posX += x;
	posY += y;
}

void Geometry::SetColor(int r, int g, int b)
{
	color = { r,g,b };
}

Vector2 Geometry::GetPosition(float anchorX, float anchorY) const
{
	Vector2 result;
	result.x = posX + anchorX * width;
	result.y = posY + anchorY * height;
	return result;
}

void Geometry::Resize(int w, int h)
{
	width = w;
	height = h;
}

Vector2 Geometry::GetSize() {
	return Vector2{ (float)width, (float)height };
}