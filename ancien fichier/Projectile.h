#pragma once
#include <SDL.h>
#include "Rectangle.h"
#include "AssetManager.h"

class Enemy; // Forward declaration

class Projectile
{
public:
    enum ProjectileOwner {
        PLAYER,
        ENEMY
    };

    Rectangle* hitbox;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    float move_speed;        
    float move_speed_y;      
    float rotation;
    ProjectileOwner owner;

    // missiles a tete chercheuse
    bool is_homing;
    float homing_speed;
    Enemy* target;

    Projectile(SDL_Renderer* renderer, const char* path, float rot, float x, float y, float speed, ProjectileOwner proj_owner, bool homing = false);
    ~Projectile();

    void Move(float deltaTime);
    void UpdateHoming(float deltaTime, Enemy* nearestEnemy);
    void Draw(SDL_Renderer* renderer);
    bool IsOutOfBounds(int screenWidth, int screenHeight);

private:
    void FindNearestEnemy();
};