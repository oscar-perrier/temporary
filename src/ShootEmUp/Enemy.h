#pragma once
#include "Entity.h"
#include "Image.h"
#include <SDL.h>

#define SPRITE_PATH "../../assets/sprites/spaceship_enemy.png"

#define PLAYER_SPEED 300.0f

const float ENEMY_FIRE_RATE = 1.0f;

class Enemy : public Entity
{
public:

    float fire_cooldown = ENEMY_FIRE_RATE;
    float move_speed = 100.0f;
    Enemy(SDL_Renderer* renderer);
    ~Enemy() override;

    void SetSprite(SDL_Renderer* renderer, const char* path);
    void Move(float x, float y);
    void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f);
    Vector2 GetPosition(float anchorX, float anchorY);
    Vector2 GetSize();
    void Draw(SDL_Renderer* renderer);
};
