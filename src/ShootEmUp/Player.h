#pragma once
#include "Entity.h"

#define PLAYER_SPRITE_PATH "../../assets/sprites/spaceship_sprite.png"

class Player : public Entity
{
public:
    // Attributs pour les upgrades
    bool has_homing_missiles;
    bool has_shield;
    float shield_timer;
    float original_fire_rate;

    Player(SDL_Renderer* renderer);
    ~Player();

    void Move(float x, float y) override;
    void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) override;
    Vector2 GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) override;
    Vector2 GetSize();
    void Draw(SDL_Renderer* renderer) override;

    int GetPV() const;
    int GetMaxPV() const;

    void Update(float deltaTime); // Nouvelle m�thode pour g�rer les timers

    // M�thodes pour les upgrades
    void ApplyHealthUpgrade();
    void ApplyHomingMissileUpgrade();
    void ApplyShieldUpgrade();
    void ApplyFireRateUpgrade();
    void TakeDamage(int damage) override;
    void ResetStatus();
    void ResetPos();

};
