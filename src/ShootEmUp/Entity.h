#pragma once
#include "Image.h"
#include "Rectangle.h"

class Entity
{
public:
    Rectangle* hitbox;
    Image* sprite;
    int pv;
    int max_pv;
    bool is_alive;
    float move_speed;
    float fire_rate;
    float fire_cooldown;
    int weapon_type;
    Vector2 spawn_point;

    // Nouveaux attributs pour les frames d'invuln�rabilit�
    bool is_invulnerable;
    float invulnerability_timer;

    Entity();
    virtual ~Entity();

    void SetSprite(SDL_Renderer* renderer, const char* path, int rot = 0, Vector2 spritePos = { 0, 0 }, Vector2 spriteSize = { 0, 0 });
    void SetHitbox();
    virtual void TakeDamage(int damage);

    virtual void Move(float x, float y) = 0;
    virtual void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) = 0;
    virtual Vector2 GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;
};