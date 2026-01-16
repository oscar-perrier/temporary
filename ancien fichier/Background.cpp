#include "Background.h"
#include "Star.h"
#include "AssetManager.h"
#include <iostream>

Background::Background(SDL_Renderer* renderer)
{
    SetSprite(renderer, BACKGROUND_SPRITE_PATH,90);
    sprite->Resize(std::max(WIDTH, HEIGHT), std::max(WIDTH, HEIGHT));
    sprite->SetPosition(0, 0, 0.0f, 0.0f);
    clone = new Image(renderer, BACKGROUND_SPRITE_PATH, 90);
    clone->Resize(std::max(WIDTH, HEIGHT), std::max(WIDTH, HEIGHT));
    clone->SetPosition(WIDTH, 0, 0.0f, 0.0f);
    randTimer = 0;
}

Background::~Background()
{
    delete clone;
}

void Background::UpdateBackground(SDL_Renderer* renderer, float deltaTime)
{
    Vector2 backgroundPos = GetPosition(0.0f, 0.0f);
    Vector2 backgroundClonePos = GetClonePosition(0.0f, 0.0f);
    Vector2 backgroundSize = GetSize();
    if (backgroundPos.x < -backgroundSize.x) {
        SetPosition(backgroundClonePos.x + backgroundSize.x, 0.0f, 0.0f, 0.0f);
        Move(-2.0f * ANIMATION_SPEED * deltaTime, 0);
    }
    if (backgroundClonePos.x < -backgroundSize.x) {
        SetClonePosition(backgroundPos.x + backgroundSize.x, 0.0f, 0.0f, 0.0f);
        CloneMove(-2.0f * ANIMATION_SPEED * deltaTime, 0);
    }
    Move(-2.0f * ANIMATION_SPEED * deltaTime, 0);
    CloneMove(-2.0f * ANIMATION_SPEED * deltaTime, 0);

    randTimer += deltaTime * 1000;
    if (randTimer >= 1500) {
        randTimer = 0;
		GenerateRandomPlanets(renderer);
    }
    for (Star* planet : randPlanets) {
        planet->Update(deltaTime);
	}
    for (int i = 0; i < randPlanets.size(); i++) {
		Vector2 planetPos = randPlanets[i]->GetPosition();
		float planetSize = randPlanets[i]->GetSize();
        if (planetPos.x < -planetSize) {
            delete randPlanets[i];
            randPlanets.erase(randPlanets.begin() + i);
            continue;
        }
	}
}

void Background::Move(float x, float y)
{
    sprite->Move(x, y);
}

void Background::CloneMove(float x, float y) {
    clone->Move(x, y);
}

void Background::SetPosition(float x, float y, float anchorX, float anchorY) {
    sprite->SetPosition(x, y, anchorX, anchorY);
}

void Background::SetClonePosition(float x, float y, float anchorX, float anchorY) {
    clone->SetPosition(x, y, anchorX, anchorY);
}

Vector2 Background::GetPosition(float anchorX, float anchorY)
{
    return sprite->GetPosition(anchorX, anchorY);
}

Vector2 Background::GetClonePosition(float anchorX, float anchorY)
{
    return clone->GetPosition(anchorX, anchorY);
}

Vector2 Background::GetSize() {
    return sprite->GetSize();
}

void Background::GenerateRandomPlanets(SDL_Renderer* renderer)
{
    // generate a random number between 0 and the length of AssetManager's animatedTextures
    AssetManager* assetManager = AssetManager::GetInstance();
    int randIndex = rand() % assetManager->animatedTextures.size();
	std::vector<SDL_Texture*> planetTextures = assetManager->animatedTextures[randIndex];
	Star* newPlanet = new Star(planetTextures, rand() % HEIGHT);
    randPlanets.push_back(newPlanet);
}

void Background::Draw(SDL_Renderer* renderer)
{
    if (sprite) {
        sprite->Draw(renderer);
        clone->Draw(renderer);
    }
}

void Background::PlanetsDraw(SDL_Renderer* renderer) {
    for (Star* planet : randPlanets) {
        planet->Draw(renderer);
		}
}
