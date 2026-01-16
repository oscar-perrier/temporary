#pragma once
#include "Entity.h"
#include "Rectangle.h"
#include <SDL.h>

enum UpgradeType {
    UPGRADE_HEALTH,
    UPGRADE_HOMING_MISSILE,
    UPGRADE_SHIELD,
    UPGRADE_FIRE_RATE
};

class Upgrade : public Entity
{
private:
    void SetSpriteByType(SDL_Renderer* renderer, UpgradeType upgradeType);

public:
    UpgradeType type;

    Upgrade(SDL_Renderer* renderer, UpgradeType upgradeType, float x, float y);
    ~Upgrade();

    void Move(float x, float y) override;
    void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) override;
    Vector2 GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) override;
    Vector2 GetSize();
    void Draw(SDL_Renderer* renderer) override;
    bool IsOutOfBounds(int screenWidth);
};