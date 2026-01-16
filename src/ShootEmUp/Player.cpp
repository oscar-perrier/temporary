#include "Player.h"
#include "ScreenManager.h"

Player::Player(SDL_Renderer* renderer)
{
    Vector2 spritePos = {12,22};
    Vector2 spriteSize = {39,41};
    SetSprite(renderer, PLAYER_SPRITE_PATH,90,spritePos,spriteSize);
    sprite->Resize(50, 50);
    sprite->SetPosition(WIDTH / 2, HEIGHT / 2, 0.5f, 0.5f);

    SetHitbox();

    pv = 3;  // Le joueur a 3 PV
    max_pv = 3;
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

void Player::SetPosition(float x, float y, float anchorX, float anchorY) {
    hitbox->SetPosition(x, y, anchorX, anchorY);
    sprite->SetPosition(x, y, anchorX, anchorY);
}

Vector2 Player::GetPosition(float anchorX, float anchorY)
{
    return hitbox->GetPosition(0.5f, 0.5f);
}

Vector2 Player::GetSize() {
    return hitbox->GetSize();
}

void Player::Draw(SDL_Renderer* renderer)
{
    if (sprite) sprite->Draw(renderer);
}
int Player::GetPV() const
{
    return pv;
}

int Player::GetMaxPV() const
{
    return max_pv;
}