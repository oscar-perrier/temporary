#include "Projectile.h"
#include "Enemy.h"
#include <cmath>

Projectile::Projectile(SDL_Renderer* renderer, const char* path, float rot, float x, float y, float speed, ProjectileOwner proj_owner, bool homing)
{
    move_speed = speed;
    rotation = rot;
    owner = proj_owner;
    is_homing = homing;
    homing_speed = 200.0f;
    target = nullptr;

    texture = AssetManager::GetInstance()->LoadTexture(renderer, path);

    switch (proj_owner) {
    case PLAYER:
        if (is_homing)
        {
            // Sprite different pour les missiles e tete chercheuse (plus gros)
            srcRect.x = 100;
            srcRect.y = 16;
            srcRect.w = 12;
            srcRect.h = 16;
        }
        else
        {
            // Sprite normal (petit projectile)
            srcRect.x = 84;
            srcRect.y = 16;
            srcRect.w = 8;
            srcRect.h = 16;
        }
        break;
    case ENEMY:
        srcRect.x = 84;
        srcRect.y = 144;
        srcRect.w = 8;
        srcRect.h = 16;
        break;
    }

    // Hitbox adaptee a la taille du sprite
    if (rotation == 90 || rotation == 270) {
        hitbox = new Rectangle(srcRect.w, srcRect.h);
    }
    else {
        hitbox = new Rectangle(srcRect.h, srcRect.w);
    }
    hitbox->SetPosition(x, y, 0.5f, 0.5f);
}

Projectile::~Projectile()
{
    delete hitbox;
}

void Projectile::Move(float deltaTime)
{
    if (is_homing && target != nullptr && target->is_alive)
    {
        Vector2 currentPos = hitbox->GetPosition(0.5f, 0.5f);
        Vector2 targetPos = target->GetPosition(0.5f, 0.5f);

        float dx = targetPos.x - currentPos.x;
        float dy = targetPos.y - currentPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance > 0)
        {
            dx = (dx / distance) * (move_speed + homing_speed);
            dy = (dy / distance) * homing_speed;

            hitbox->Move(dx * deltaTime, dy * deltaTime);
            rotation = std::atan2(dy, dx) * 180.0f / 3.14159f;
        }
    }
    else
    {
        if (is_homing)
        {
            target = nullptr;
        }
        hitbox->Move(move_speed * deltaTime, 0);
    }
}

void Projectile::UpdateHoming(float deltaTime, Enemy* nearestEnemy)
{
    if (is_homing && nearestEnemy != nullptr)
    {
        target = nearestEnemy;
    }
}

void Projectile::Draw(SDL_Renderer* renderer)
{
    if (texture)
    {
        SDL_Rect dst;
        Vector2 pos = hitbox->GetPosition(0.5f, 0.5f);

        dst.x = static_cast<int>(pos.x - hitbox->GetSize().x / 2);
        dst.y = static_cast<int>(pos.y - hitbox->GetSize().y / 2);
        dst.w = static_cast<int>(hitbox->GetSize().x);
        dst.h = static_cast<int>(hitbox->GetSize().y);

        SDL_RenderCopyEx(renderer, texture, &srcRect, &dst, rotation, nullptr, SDL_FLIP_NONE);
    }
    else
    {
        hitbox->Draw(renderer);
    }
}

bool Projectile::IsOutOfBounds(int screenWidth, int screenHeight)
{
    Vector2 pos = hitbox->GetPosition(0.5f, 0.5f);
    return pos.x > screenWidth + 50 || pos.x < -50 || pos.y > screenHeight + 50 || pos.y < -50;
}