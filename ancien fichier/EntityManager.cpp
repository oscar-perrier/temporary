#include "EntityManager.h"
#include "GameManager.h"
#include <iostream>
#include <cmath>

EntityManager::~EntityManager() {
    for (auto& e : enemies) delete e;
    for (auto& b : bullets) delete b;
    for (auto& u : upgrades) delete u;
    delete player;
    delete background;
}

void EntityManager::Init(SDL_Renderer* renderer, Menu menu)
{
    player = new Player(renderer);
    background = new Background(renderer);
    currentState = menu;
    if (!startButton) startButton = new Button(renderer, "Start", WIDTH / 2 - 150, HEIGHT / 4 - 100, 300, 200);
    if (!quitButton) quitButton = new Button(renderer, "Quit", WIDTH / 2 - 150, 3 * HEIGHT / 4 - 100, 300, 200);
    if (!retryButton) retryButton = new Button(renderer, "Retry", WIDTH / 2 - 150, HEIGHT / 4 - 100, 300, 200);
    if (!menuButton) menuButton = new Button(renderer, "Main Menu", WIDTH / 2 - 150, 3 * HEIGHT / 4 - 100, 300, 200);
}

void EntityManager::Update(SDL_Renderer* renderer, InputManager& inputs, float deltaTime)
{
    player->Update(deltaTime);


    if (currentState == MainMenu) {
        startButton->SetPosition(WIDTH / 2 - 150, HEIGHT / 4 - 100);
        quitButton->SetPosition(WIDTH / 2 - 150, 3 * HEIGHT / 4 - 100);
        retryButton->SetPosition(WIDTH * 2, HEIGHT * 2);
        menuButton->SetPosition(WIDTH * 2, HEIGHT * 2);
    }
    if (currentState == Defeat) {
        startButton->SetPosition(WIDTH * 2, HEIGHT * 2);
        quitButton->SetPosition(WIDTH * 2, 3 * HEIGHT * 2);
        retryButton->SetPosition(WIDTH / 2 - 150, HEIGHT / 4 - 100);
        menuButton->SetPosition(WIDTH / 2 - 150, 3 * HEIGHT / 4 - 100);
    }

    // D�placement joueur
    float movX = 0.f, movY = 0.f;
    Vector2 posPlayer = player->GetPosition(0.5f, 0.5f);
    Vector2 sizePlayer = player->GetSize();

    if (inputs.IsHeld(SDLK_z) && posPlayer.y - (sizePlayer.y / 2) > 0) movY -= 1.0f;
    else if (inputs.IsHeld(SDLK_z)) player->SetPosition(posPlayer.x, 0.0f + (sizePlayer.y / 2), 0.5f, 0.5f);
    if (inputs.IsHeld(SDLK_q) && posPlayer.x - (sizePlayer.x / 2) > 0) movX -= 1.0f;
    else if (inputs.IsHeld(SDLK_q)) player->SetPosition(0.0f + (sizePlayer.x / 2), posPlayer.y, 0.5f, 0.5f);
    if (inputs.IsHeld(SDLK_s) && posPlayer.y + (sizePlayer.y / 2) < HEIGHT - 1) movY += 1.0f;
    else if (inputs.IsHeld(SDLK_s)) player->SetPosition(posPlayer.x, HEIGHT - 1 - (sizePlayer.y / 2), 0.5f, 0.5f);
    if (inputs.IsHeld(SDLK_d) && posPlayer.x + (sizePlayer.x / 2) < WIDTH - 1) movX += 1.0f;
    else if (inputs.IsHeld(SDLK_d)) player->SetPosition(WIDTH - 1 - (sizePlayer.x / 2), posPlayer.y, 0.5f, 0.5f);

    if (movX != 0 || movY != 0)
    {
        float length = std::sqrt(movX * movX + movY * movY);
        movX = (movX / length) * PLAYER_SPEED;
        movY = (movY / length) * PLAYER_SPEED;
        player->Move(movX * deltaTime, movY * deltaTime);
    }

    if (player->fire_cooldown > 0) player->fire_cooldown -= deltaTime;
    if (inputs.IsHeld(SDLK_SPACE) && player->fire_cooldown <= 0)
    {
        Projectile* bullet = new Projectile(renderer,
            "../../assets/sprites/bullets_sprite.png",
            90,
            posPlayer.x + 20,
            posPlayer.y,
            500.f,
            Projectile::PLAYER,
            player->has_homing_missiles);
        bullets.push_back(bullet);
        player->fire_cooldown = 1.0f / player->fire_rate;
    }

    for (auto& enemy : enemies)
    {
        enemy->Move(-enemy->move_speed * deltaTime, 0);
        Vector2 posEnemy = enemy->GetPosition(0.5f, 0.5f);
        if (posEnemy.x < -50)
        {
            enemy->SetPosition(WIDTH + 50, posEnemy.y, 0.5f, 0.5f);
        }
    }

    for (auto& enemy : enemies)
    {
        if (!enemy->can_shoot) continue;

        if (enemy->fire_cooldown > 0)
            enemy->fire_cooldown -= deltaTime;

        if (enemy->fire_cooldown <= 0)
        {
            Vector2 posEnemy = enemy->GetPosition(0.5f, 0.5f);

            if (enemy->enemy_type == ENEMY_BOSS)
            {
                for (int i = 0; i < 5; i++)
                {
                    float randomAngle = ((rand() % 90) - 45) * 3.14159f / 180.0f;
                    float speedX = -500.0f * cos(randomAngle);
                    float speedY = -500.0f * sin(randomAngle);
                    float rotation = atan2(speedY, speedX) * 180.0f / 3.14159f;

                    Projectile* bullet = new Projectile(renderer,
                        "../../assets/sprites/bullets_sprite.png",
                        rotation,
                        posEnemy.x - 75,
                        posEnemy.y + (rand() % 60 - 30),
                        speedX,
                        Projectile::ENEMY);

                    bullet->move_speed_y = speedY;
                    bullets.push_back(bullet);
                }
                enemy->fire_cooldown = rand() % 2 + 1.0f / enemy->fire_rate;
            }
            else
            {
                Projectile* bullet = new Projectile(renderer,
                    "../../assets/sprites/bullets_sprite.png",
                    0,
                    posEnemy.x - 20,
                    posEnemy.y,
                    -500.f,
                    Projectile::ENEMY);
                bullets.push_back(bullet);
                enemy->fire_cooldown = rand() % 2 + 1.0f / enemy->fire_rate;
            }
        }
    }

    // ✅ MOUVEMENT DES BULLETS
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->is_homing && bullets[i]->owner == Projectile::PLAYER)
        {
            Enemy* nearest = FindNearestEnemy(bullets[i]->hitbox->GetPosition(0.5f, 0.5f));
            bullets[i]->UpdateHoming(deltaTime, nearest);
        }

        bullets[i]->Move(deltaTime);

        if (bullets[i]->IsOutOfBounds(WIDTH, HEIGHT))
        {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            continue;
        }
    }

    for (int i = 0; i < upgrades.size(); i++)
    {
        upgrades[i]->Move(-upgrades[i]->move_speed * deltaTime, 0);
        if (upgrades[i]->IsOutOfBounds(WIDTH))
        {
            delete upgrades[i];
            upgrades.erase(upgrades.begin() + i);
            continue;
        }
    }

    CheckCollisions(renderer);
    CheckUpgradeCollisions();
    background->UpdateBackground(renderer, deltaTime);
}

void EntityManager::CheckCollisions(SDL_Renderer* renderer)
{
    for (int i = bullets.size() - 1; i >= 0; i--)
    {
        if (bullets[i]->owner == Projectile::ENEMY)
        {
            if (static_cast<Rectangle*>(bullets[i]->hitbox)->Intersects(static_cast<Rectangle*>(player->hitbox)))
            {
                if (player->has_shield && player->shield_timer > 0)
                {
                    delete bullets[i];
                    bullets.erase(bullets.begin() + i);
                    continue;
                }

                player->TakeDamage(1);
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                if (!player->is_alive)
                {
                    //std::cout << "GAME OVER!" << std::endl;
                    for (auto& e : enemies) delete e;
                    enemies.clear();
                    for (auto& b : bullets) delete b;
                    bullets.clear();
                    for (auto& u : upgrades) delete u;
                    upgrades.clear();
                    player->ResetPos();
                    currentState = Defeat;
                    return;
                }
                continue;
            }
        }
        else if (bullets[i]->owner == Projectile::PLAYER)
        {
            bool bulletDestroyed = false;
            for (int j = enemies.size() - 1; j >= 0; j--)
            {
                if (static_cast<Rectangle*>(bullets[i]->hitbox)->Intersects(static_cast<Rectangle*>(enemies[j]->hitbox)))
                {
                    enemies[j]->TakeDamage(1);
                    delete bullets[i];
                    bullets.erase(bullets.begin() + i);
                    bulletDestroyed = true;

                    if (!enemies[j]->is_alive)
                    {
                        Enemy* dyingEnemy = enemies[j];
                        for (auto& bullet : bullets)
                        {
                            if (bullet->target == dyingEnemy)
                            {
                                bullet->target = nullptr;
                            }
                        }

                        if (rand() % 100 < 20)
                        {
                            Vector2 enemyPos = enemies[j]->GetPosition(0.5f, 0.5f);
                            UpgradeType randomType = (UpgradeType)(rand() % 4);
                            Upgrade* upgrade = new Upgrade(renderer, randomType, enemyPos.x, enemyPos.y);
                            upgrades.push_back(upgrade);
                        }

                        delete enemies[j];
                        enemies.erase(enemies.begin() + j);
                    }
                    break;
                }
            }
            if (currentState == MainMenu) {
                if (static_cast<Rectangle*>(bullets[i]->hitbox)->Intersects(static_cast<Rectangle*>(startButton->hitbox))) {
                    for (auto& b : bullets) delete b;
                    bullets.clear();
                    bulletDestroyed = true;
                    currentState = PlayingLevel;
                    return;
                }

                if (static_cast<Rectangle*>(bullets[i]->hitbox)->Intersects(static_cast<Rectangle*>(quitButton->hitbox))) {
                    for (auto& b : bullets) delete b;
                    bullets.clear();
                    bulletDestroyed = true;
                    currentState = Quit;
                    return;
                }
            }

            if (currentState == Defeat) {
                if (static_cast<Rectangle*>(bullets[i]->hitbox)->Intersects(static_cast<Rectangle*>(retryButton->hitbox))) {
                    for (auto& b : bullets) delete b;
                    bullets.clear();
                    currentState = PlayingLevel;
                    player->ResetStatus();
                    return;
                }

                if (static_cast<Rectangle*>(bullets[i]->hitbox)->Intersects(static_cast<Rectangle*>(menuButton->hitbox))) {
                    for (auto& b : bullets) delete b;
                    bullets.clear();
                    currentState = MainMenu;
                    player->ResetStatus();
                    return;
                }
            }
            if (bulletDestroyed) continue;
        }
    }

    for (int i = enemies.size() - 1; i >= 0; i--)
    {
        if (static_cast<Rectangle*>(player->hitbox)->Intersects(static_cast<Rectangle*>(enemies[i]->hitbox)))
        {
            if (player->has_shield && player->shield_timer > 0)
            {
                Enemy* dyingEnemy = enemies[i];
                for (auto& bullet : bullets)
                {
                    if (bullet->target == dyingEnemy)
                    {
                        bullet->target = nullptr;
                    }
                }

                enemies[i]->TakeDamage(enemies[i]->max_pv);
                if (!enemies[i]->is_alive)
                {
                    delete enemies[i];
                    enemies.erase(enemies.begin() + i);
                }
                continue;
            }

            player->TakeDamage(1);

            Enemy* dyingEnemy = enemies[i];
            for (auto& bullet : bullets)
            {
                if (bullet->target == dyingEnemy)
                {
                    bullet->target = nullptr;
                }
            }

            enemies[i]->TakeDamage(enemies[i]->max_pv);
            if (!enemies[i]->is_alive)
            {
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
            }
            if (!player->is_alive)
            {
            }
        }
    }
}

void EntityManager::CheckUpgradeCollisions()
{
    for (int i = upgrades.size() - 1; i >= 0; i--)
    {
        if (static_cast<Rectangle*>(upgrades[i]->hitbox)->Intersects(static_cast<Rectangle*>(player->hitbox)))
        {
            switch (upgrades[i]->type)
            {
            case UPGRADE_HEALTH:
                player->ApplyHealthUpgrade();
                break;
            case UPGRADE_HOMING_MISSILE:
                player->ApplyHomingMissileUpgrade();
                break;
            case UPGRADE_SHIELD:
                player->ApplyShieldUpgrade();
                break;
            case UPGRADE_FIRE_RATE:
                player->ApplyFireRateUpgrade();
                break;
            }
            delete upgrades[i];
            upgrades.erase(upgrades.begin() + i);
        }
    }
}

Enemy* EntityManager::FindNearestEnemy(const Vector2& position)
{
    Enemy* nearest = nullptr;
    float minDistance = 999999.0f;
    for (auto& enemy : enemies)
    {
        if (!enemy->is_alive) continue;
        Vector2 enemyPos = enemy->GetPosition(0.5f, 0.5f);
        float dx = enemyPos.x - position.x;
        float dy = enemyPos.y - position.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        if (distance < minDistance)
        {
            minDistance = distance;
            nearest = enemy;
        }
    }
    return nearest;
}

Player* EntityManager::GetPlayer() { return player; }
std::vector<Enemy*> EntityManager::GetEnemies() { return enemies; }
std::vector<Projectile*> EntityManager::GetBullets() { return bullets; }
std::vector<Upgrade*> EntityManager::GetUpgrades() { return upgrades; }
Background* EntityManager::GetBackground() { return background; }
void EntityManager::AddEnemy(Enemy* e) { enemies.push_back(e); }
void EntityManager::AddBullet(Projectile* b) { bullets.push_back(b); }
void EntityManager::AddUpgrade(Upgrade* u) { upgrades.push_back(u); }

Button* EntityManager::GetStartButton() {
    return startButton;
}

Button* EntityManager::GetQuitButton() {
    return quitButton;
}

Button* EntityManager::GetRetryButton() {
    return retryButton;
}

Button* EntityManager::GetMenuButton() {
    return menuButton;
}

Menu EntityManager::CheckState() {
    return currentState;
}

void EntityManager::SetState(Menu state) {
    currentState = state;
}
