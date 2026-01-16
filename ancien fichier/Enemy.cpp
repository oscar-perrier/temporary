#include "Enemy.h"
#include "ScreenManager.h"

Enemy::Enemy(SDL_Renderer* renderer, EnemyType type)
{
    enemy_type = type;
    SetupByType(renderer, type);
}

void Enemy::SetupByType(SDL_Renderer* renderer, EnemyType type)
{
    switch (type)
    {
    case ENEMY_NORMAL:
        sprite = new Image(renderer, "../../assets/sprites/spaceship_enemy.png", 90, 33, 11, 46, 63);
        sprite->Resize(50, 50);
        move_speed = 100.0f;
        pv = 1;
        max_pv = 1;
        can_shoot = true;
        fire_rate = ENEMY_FIRE_RATE;
        break;

    case ENEMY_OBSTACLE:
        // Utilise un sprite diff�rent pour les obstacles 
        sprite = new Image(renderer, "../../assets/sprites/mine_sprite.png", 90, 16, 48, 31, 31);
        sprite->Resize(60, 60);
        move_speed = 80.0f;
        pv = 3; // Plus r�sistant
        max_pv = 3;
        can_shoot = false; // Ne tire pas
        break;

    case ENEMY_TANK:
        // Sprite diff�rent pour le tank
        sprite = new Image(renderer, "../../assets/sprites/spaceship_boss.png", 90, 3, 36, 108, 105);
        sprite->Resize(70, 70);
        move_speed = 50.0f; // Plus lent
        pv = 5; // Plus de PV
        max_pv = 5;
        can_shoot = true;
        fire_rate = ENEMY_FIRE_RATE * 2.0f; // Tire 2x plus vite
        break;

    case ENEMY_BOSS:
        sprite = new Image(renderer, "../../assets/sprites/shrek.png", 90);
        sprite->Resize(150, 150);  
        move_speed = 30.0f;  
        pv = 100;  
        max_pv = 50;
        can_shoot = true;
        fire_rate = ENEMY_FIRE_RATE * 3.0f;  
        break;
    }

    sprite->SetPosition(WIDTH - 50, HEIGHT / 2, 0.5f, 0.5f);
    SetHitbox();
}

void Enemy::SetSprite(SDL_Renderer* renderer, const char* path)
{
    sprite = new Image(renderer, "../../assets/sprites/spaceship_enemy.png", 90, 33, 11, 46, 63);
    sprite->Resize(50, 50);
    sprite->SetPosition(WIDTH - 50, HEIGHT / 2, 0.5f, 0.5f);
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

void Enemy::SetPosition(float x, float y, float anchorX, float anchorY)
{
    hitbox->SetPosition(x, y, anchorX, anchorY);
    sprite->SetPosition(x, y, anchorX, anchorY);
}

Vector2 Enemy::GetPosition(float anchorX, float anchorY)
{
    return hitbox->GetPosition(0.5f, 0.5f);
}

Vector2 Enemy::GetSize()
{
    return hitbox->GetSize();
}

void Enemy::Draw(SDL_Renderer* renderer)
{
    if (sprite) sprite->Draw(renderer);
}