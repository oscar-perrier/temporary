#pragma once
#include <vector>
#include <SDL.h>
#include <ScreenManager.h>
class Star
{
	std::vector<SDL_Texture*> frames;
    float next_frame = 0.f;
    int current_frame = 0;
    float size;
    float rot;
    float posX;
	float posY;
	float randomAnimSpeed;

public:
    Star(std::vector<SDL_Texture*> frames, int y);
    void Update(float deltaTime);
	Vector2 GetPosition() { return Vector2{ posX, posY }; }
	float GetSize() { return size; }
	void Draw(SDL_Renderer* renderer);
};

