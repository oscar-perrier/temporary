#include "Star.h"

Star::Star(std::vector<SDL_Texture*> frames, int y)
	: frames(frames), posY(y)
{
	posX = WIDTH;
	rot = rand() % 360;
	size = rand() % HEIGHT / 8 + 20;
	randomAnimSpeed = rand() % 20 + 10;
}

void Star::Update(float deltaTime)
{
	next_frame += randomAnimSpeed * deltaTime;
	if (next_frame >= 1.f) {
		current_frame = (current_frame + 1) % frames.size();
		next_frame = 0.f;
	}
	posX -= size*1.5f * deltaTime;
}

void Star::Draw(SDL_Renderer* renderer)
{
	SDL_Rect destRect = { posX, posY, size, size };
	SDL_RenderCopyEx(renderer, frames[current_frame], NULL, &destRect, rot, NULL, SDL_FLIP_NONE);
}