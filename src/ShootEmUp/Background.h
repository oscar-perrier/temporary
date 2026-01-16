#pragma once
#include "Entity.h"
#include "Image.h"
#include "AssetManager.h"
#include <SDL.h>
#include <vector>

class AssetManager;
class Star;

#define BACKGROUND_SPRITE_PATH "../../assets/background/png/background_blue.png"

#define ANIMATION_SPEED 20.f

class Background : public Entity
{
public:
    Image* clone;
	std::vector<Star*> randPlanets;
    float randTimer;


    Background(SDL_Renderer* renderer);
    ~Background() override;

    void UpdateBackground(SDL_Renderer* renderer, float deltaTime);
    void Move(float x, float y);
    void CloneMove(float x, float y);
    void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f);
    void SetClonePosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f);
    Vector2 GetPosition(float anchorX, float anchorY);
    Vector2 GetClonePosition(float anchorX, float anchorY);
    Vector2 GetSize();
	void GenerateRandomPlanets(SDL_Renderer* renderer);
    void Draw(SDL_Renderer* renderer);
    void PlanetsDraw(SDL_Renderer* renderer);
};