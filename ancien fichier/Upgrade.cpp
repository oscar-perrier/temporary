#include "Upgrade.h"
#include "ScreenManager.h"

Upgrade::Upgrade(SDL_Renderer* renderer, UpgradeType upgradeType, float x, float y)
{
    type = upgradeType;
    move_speed = 100.0f; // Vitesse de défilement vers la gauche

    SetSpriteByType(renderer, upgradeType);
    sprite->Resize(40, 40);
    sprite->SetPosition(x, y, 0.5f, 0.5f);

    SetHitbox();
}

Upgrade::~Upgrade()
{
    if (hitbox) delete hitbox;
}

void Upgrade::SetSpriteByType(SDL_Renderer* renderer, UpgradeType upgradeType)
{
    // Utilise différentes parties du sprite sheet selon le type
    switch (upgradeType)
    {
    case UPGRADE_HEALTH:
        sprite = new Image(renderer, "../../assets/sprites/bonus_sprite.png", 0, 5, 5, 21, 21);
        break;
    case UPGRADE_HOMING_MISSILE:
        sprite = new Image(renderer, "../../assets/sprites/bonus_sprite.png", 0, 69, 5, 21, 21);
        break;
    case UPGRADE_SHIELD:
        sprite = new Image(renderer, "../../assets/sprites/bonus_sprite.png", 0, 37, 5, 21, 21);
        break;
    case UPGRADE_FIRE_RATE:
        sprite = new Image(renderer, "../../assets/sprites/bonus_sprite.png", 0, 101, 5, 21, 21);
        break;
    }
}

void Upgrade::Move(float x, float y)
{
    hitbox->Move(x, y);
    sprite->Move(x, y);
}

void Upgrade::SetPosition(float x, float y, float anchorX, float anchorY)
{
    hitbox->SetPosition(x, y, anchorX, anchorY);
    sprite->SetPosition(x, y, anchorX, anchorY);
}

Vector2 Upgrade::GetPosition(float anchorX, float anchorY)
{
    return hitbox->GetPosition(anchorX, anchorY);
}

Vector2 Upgrade::GetSize()
{
    return hitbox->GetSize();
}

void Upgrade::Draw(SDL_Renderer* renderer)
{
    if (sprite) sprite->Draw(renderer);
}

bool Upgrade::IsOutOfBounds(int screenWidth)
{
    Vector2 pos = hitbox->GetPosition(0.5f, 0.5f);
    return pos.x < -50;
}