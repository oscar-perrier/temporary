#include "Enemy.h"
#include "ScreenManager.h"

Enemy::Enemy(SDL_Renderer* renderer)
{
    SetSprite(renderer, SPRITE_PATH);

    SetHitbox();
    pv = 1;  // L'ennemi a 1 PV
    max_pv = 1;
}

void Enemy::SetSprite(SDL_Renderer* renderer, const char* path)
{
    sprite = new Image(renderer, "../../assets/sprites/spaceship_enemy.png", 90, 33, 11, 46, 63);

    sprite->Resize(50, 50);
    sprite->SetPosition(WIDTH - 50, HEIGHT / 2, 0.5f, 0.5f);  // Apparaît à droite
}

Enemy::~Enemy()
{
    delete hitbox;
} 

void Enemy::Move(float x, float y)
{
    hitbox->Move(x, y);
    sprite->Move(x, y);
}

void Enemy::SetPosition(float x, float y, float anchorX, float anchorY) {
    hitbox->SetPosition(x, y, anchorX, anchorY);
    sprite->SetPosition(x, y, anchorX, anchorY);
}

Vector2 Enemy::GetPosition(float anchorX, float anchorY)
{
    return hitbox->GetPosition(0.5f, 0.5f);
}

Vector2 Enemy::GetSize() {
    return hitbox->GetSize();
}

void Enemy::Draw(SDL_Renderer* renderer)
{
    if (sprite) sprite->Draw(renderer);
}