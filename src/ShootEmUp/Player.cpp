#include "Player.h"
#include "ScreenManager.h"
#include <iostream>

Player::Player(SDL_Renderer* renderer)
{
    Vector2 spritePos = { 12,22 };
    Vector2 spriteSize = { 39,41 };
    SetSprite(renderer, PLAYER_SPRITE_PATH, 90, spritePos, spriteSize);
    sprite->Resize(50, 50);
    sprite->SetPosition(WIDTH / 4, HEIGHT / 2, 0.5f, 0.5f);

    SetHitbox();

    pv = 3;
    max_pv = 3;

    has_homing_missiles = false;
    has_shield = false;
    shield_timer = 0.0f;
    fire_rate = FIRE_RATE;
    original_fire_rate = FIRE_RATE;
    fire_cooldown = 0.0f;
}

Player::~Player()
{
    delete hitbox;
}

void Player::Move(float x, float y)
{
    hitbox->Move(x, y);
    sprite->Move(x, y);
}

void Player::ResetStatus()
{
    pv = 3;
    is_alive = true;
    has_homing_missiles = false;
    has_shield = false;
    shield_timer = 0.0f;
    is_invulnerable = false;
    fire_rate = FIRE_RATE;
}

void Player::ResetPos() {
    SetPosition(WIDTH / 4, HEIGHT / 2, 0.5f, 0.5f);
}

void Player::SetPosition(float x, float y, float anchorX, float anchorY) {
    hitbox->SetPosition(x, y, anchorX, anchorY);
    sprite->SetPosition(x, y, anchorX, anchorY);
}

Vector2 Player::GetPosition(float anchorX, float anchorY)
{
    return hitbox->GetPosition(0.5f, 0.5f);
}

Vector2 Player::GetSize()
{
    return hitbox->GetSize();
}

void Player::Draw(SDL_Renderer* renderer)
{
    if (is_invulnerable)
    {
        int blinkCycle = (int)(invulnerability_timer * 10) % 2;
        if (blinkCycle == 0 && sprite)
        {
            sprite->Draw(renderer);
        }
    }
    else if (sprite)
    {
        sprite->Draw(renderer);
    }

    if (has_shield && shield_timer > 0)
    {
        Vector2 pos = GetPosition(0.5f, 0.5f);
        Vector2 size = GetSize();
        int radius = (int)(size.x * 0.8f);

        for (int i = 0; i < 3; i++)
        {
            SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
            for (int angle = 0; angle < 360; angle += 10)
            {
                float rad = angle * 3.14159f / 180.0f;
                int x = (int)(pos.x + (radius + i) * cos(rad));
                int y = (int)(pos.y + (radius + i) * sin(rad));
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void Player::Update(float deltaTime)
{
    if (is_invulnerable)
    {
        invulnerability_timer -= deltaTime;
        if (invulnerability_timer <= 0)
        {
            is_invulnerable = false;
            invulnerability_timer = 0;
        }
    }

    if (has_shield && shield_timer > 0)
    {
        shield_timer -= deltaTime;
        if (shield_timer <= 0)
        {
            has_shield = false;
            shield_timer = 0;
        }
    }
}

void Player::TakeDamage(int damage)
{
    if (is_invulnerable) return; 

    pv -= damage;
    if (pv <= 0)
    {
        pv = 0;
        is_alive = false;
    }
    is_invulnerable = true;
    invulnerability_timer = 0.5f;
}


int Player::GetPV() const
{
    return pv;
}

int Player::GetMaxPV() const
{
    return max_pv;
}

void Player::ApplyHealthUpgrade()
{
    if (pv < max_pv)
    {
        pv++;
    }
}

void Player::ApplyHomingMissileUpgrade()
{
    has_homing_missiles = true;
}

void Player::ApplyShieldUpgrade()
{
    has_shield = true;
    shield_timer = 5.0f;
    is_invulnerable = true;
}

void Player::ApplyFireRateUpgrade()
{
    fire_rate = original_fire_rate * 2.0f;
}