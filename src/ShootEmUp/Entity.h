#pragma once
#include "Geometry.h"
#include "Rectangle.h"
#include <SDL.h>
#include <Image.h>

class Entity
{
public:
    Geometry* hitbox;
    Image* sprite;
    int pv;
    float move_speed;
    float fire_rate;
    int weapon_type;
    Vector2 spawn_point;
    int max_pv;
    bool is_alive;

    Entity();
    virtual ~Entity();

    void SetSprite(SDL_Renderer* renderer, const char* path, int rot, Vector2 spritePos = { 0 }, Vector2 spriteSize = { 0 });
    void SetHitbox();
    void TakeDamage(int damage);
    void SetPosition(float x, float y, float anchorX, float anchorY);
    void SetPosition(const Vector2& position, float anchorX, float anchorY);


    virtual void Update(float deltaTime) {}
    virtual void Draw(SDL_Renderer* renderer) {}
};
