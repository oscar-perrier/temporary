#include "Entity.h"
#include <iostream>

Entity::Entity()
{
    hitbox = nullptr;
    sprite = nullptr;
    pv = 1;
    max_pv = 1;
    is_alive = true;
    move_speed = 0;
    fire_rate = 0;
    fire_cooldown = 0;
    weapon_type = 0;
    spawn_point = { 0 };
    is_invulnerable = false;
    invulnerability_timer = 0.0f;
}

Entity::~Entity()
{
    if (sprite) delete sprite;
}

void Entity::SetSprite(SDL_Renderer* renderer, const char* path, int rot, Vector2 spritePos, Vector2 spriteSize)
{
    if (spriteSize.x == 0.0f || spriteSize.y == 0.0f) {
        sprite = new Image(renderer, path, rot);
    }
    else {
        sprite = new Image(renderer, path, rot, spritePos.x, spritePos.y, spriteSize.x, spriteSize.y);
    }
}

void Entity::SetHitbox()
{
    hitbox = new Rectangle(
        sprite->GetSize().x,
        sprite->GetSize().y
    );
    Vector2 pos = sprite->GetPosition(0.5f, 0.5f);
    hitbox->SetPosition(pos);
}

void Entity::TakeDamage(int damage)
{
    pv -= damage;
    if (pv <= 0)
    {
        pv = 0;
        is_alive = false;
    }

    // Active l'invulnérabilité pour 0.5 secondes


}