#include "Projectile.h"

Projectile::Projectile(SDL_Renderer* renderer, const char* path, float rot, float x, float y, float speed, ProjectileOwner proj_owner)
{
    move_speed = speed;
    rotation = rot;
    owner = proj_owner;

    // Texture
    texture = AssetManager::GetInstance()->LoadTexture(renderer, path);

    // Portion du sprite sheet (84,16 ? 91,31)
    srcRect.x = 84;
    srcRect.y = 16;
    srcRect.w = 8;
    srcRect.h = 16;

    // Hitbox
    if (rotation == 90 || rotation == 270) {
        hitbox = new Rectangle(srcRect.h, srcRect.w);
    }
    else if (rotation == 180 || rotation == 0) {
        hitbox = new Rectangle(srcRect.w, srcRect.h);
    }
    hitbox->SetPosition(x, y, 0.5f, 0.5f);

}

void Projectile::Move(float deltaTime)
{
    hitbox->Move(move_speed * deltaTime, 0);
}

void Projectile::Draw(SDL_Renderer* renderer)
{
    if (texture)
    {
        SDL_Rect dst;
        Vector2 pos = hitbox->GetPosition(0.5f, 0.5f);
        if (rotation == 90 || rotation == 270) {
            dst.x = static_cast<int>(pos.x - hitbox->GetSize().y / 2);
            dst.y = static_cast<int>(pos.y - hitbox->GetSize().x / 2);
            dst.w = static_cast<int>(hitbox->GetSize().y);
            dst.h = static_cast<int>(hitbox->GetSize().x);
        }
        else if (rotation == 180 || rotation == 0) {
            dst.x = static_cast<int>(pos.x - hitbox->GetSize().x / 2);
            dst.y = static_cast<int>(pos.y - hitbox->GetSize().y / 2);
            dst.w = static_cast<int>(hitbox->GetSize().x);
            dst.h = static_cast<int>(hitbox->GetSize().y);
        }

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
    return pos.x > screenWidth || pos.x < 0 || pos.y > screenHeight || pos.y < 0;
}
