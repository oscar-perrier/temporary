#pragma once
#include "Entity.h"
#include "Image.h"
#include <SDL.h>

class ScreenManager;

#define PLAYER_SPRITE_PATH "../../assets/sprites/spaceship_sprite.png"

#define PLAYER_SPEED 300.0f
#define FIRE_RATE 3.f

class Player : public Entity
{
public:
    float fire_cooldown = 1.0f / FIRE_RATE;
    int GetPV() const;
    int GetMaxPV() const;
    Player(SDL_Renderer* renderer);
    ~Player() override;

    void Move(float x, float y);
    void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f);
    Vector2 GetPosition(float anchorX, float anchorY);
    Vector2 GetSize();
    void Draw(SDL_Renderer* renderer);
};
