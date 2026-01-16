#pragma once
#include "Entity.h"
#include "Rectangle.h"
#include "AssetManager.h"
#include <SDL.h>

class Projectile : public Entity
{
public:
    SDL_Texture* texture;
    float rotation;
    SDL_Rect srcRect;
    enum ProjectileOwner { PLAYER, ENEMY };
    ProjectileOwner owner;
    Projectile(SDL_Renderer* renderer, const char* path, float rotation, float x, float y, float speed, ProjectileOwner proj_owner);

    void Move(float deltaTime);
    void Draw(SDL_Renderer* renderer);
    bool IsOutOfBounds(int screenWidth, int screenHeight);
};
