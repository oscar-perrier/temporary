#pragma once
#include "Entity.h"

#define SPRITE_PATH "../../assets/sprites/spaceship_enemy.png"

enum EnemyType {
    ENEMY_NORMAL,      // Ennemi normal qui tire
    ENEMY_OBSTACLE,    // Obstacle qui ne tire pas
    ENEMY_TANK,         // Ennemi lent mais qui tire vite
    ENEMY_BOSS
};

class Enemy : public Entity
{
public:
    EnemyType enemy_type;
    bool can_shoot;

    Enemy(SDL_Renderer* renderer, EnemyType type = ENEMY_NORMAL);
    ~Enemy();

    void Move(float x, float y) override;
    void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) override;
    Vector2 GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) override;
    Vector2 GetSize();
    void Draw(SDL_Renderer* renderer) override;

private:
    void SetSprite(SDL_Renderer* renderer, const char* path);
    void SetupByType(SDL_Renderer* renderer, EnemyType type);
};