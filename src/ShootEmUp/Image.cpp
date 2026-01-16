#include "Image.h"
#include "AssetManager.h"

#include <SDL.h>
#include <iostream>

Image::Image(SDL_Renderer* renderer, const char* path, int rot, int spritePosX, int spritePosY, int spriteWidth, int spriteHeight) : Geometry(-1,-1)
{
	texture = AssetManager::GetInstance()->LoadTexture(renderer, path);
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	if (spriteWidth > 0 && spriteHeight > 0 && spritePosX > 0 && spritePosY > 0) {
		srcRect = new SDL_Rect{ spritePosX,spritePosY,spriteWidth,spriteHeight };
		width = spriteWidth;
		height = spriteHeight;
	}
	else {
		srcRect = nullptr;
	}
	drawSize = Vector2{ (float)width, (float)height };
	rotation = rot;
}

void Image::Resize(int w, int h)
{
	float factorW = (float)w / (float)width;
	float factorH = (float)h / (float)height;

	float factorMin = std::min(factorW, factorH);

	float newWidth = width * factorMin;
	float newHeight = height * factorMin;

	drawSize = Vector2{ newWidth, newHeight };
}

void Image::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { posX,posY,drawSize.x,drawSize.y };
	if (srcRect == nullptr) {
		SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotation, NULL, SDL_FLIP_NONE);
	}
	else {
		SDL_RenderCopyEx(renderer, texture, srcRect, &rect, rotation, NULL, SDL_FLIP_NONE);
	}
}

Vector2 Image::GetSize() {
	return drawSize;
}

Vector2 Image::GetPosition(float anchorX, float anchorY) const
{
	Vector2 result;
	result.x = posX + anchorX * drawSize.x;
	result.y = posY + anchorY * drawSize.y;
	return result;
}

void Image::SetPosition(float x, float y, float anchorX, float anchorY)
{
	posX = x - drawSize.x * anchorX;
	posY = y - drawSize.y * anchorY;
}

void Image::SetPosition(const Vector2& position, float anchorX, float anchorY)
{
	SetPosition(position.x, position.y, anchorX, anchorY);
}
bool Image::Intersects(const Geometry* other) const
{
	// Les images n'ont pas de collision dans ce jeu
	return false;
}