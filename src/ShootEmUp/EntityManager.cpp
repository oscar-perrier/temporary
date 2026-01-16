#include "EntityManager.h"
#include <iostream>

EntityManager::~EntityManager() {
    for (auto& e : enemies) delete e;
    for (auto& b : bullets) delete b;
    delete player;
	delete background;
}

void EntityManager::Init(SDL_Renderer* renderer)
{
    player = new Player(renderer);
    Enemy* enemy1 = new Enemy(renderer);
    

    enemies.push_back(enemy1);

    background = new Background(renderer);
}

void EntityManager::Update(SDL_Renderer* renderer, InputManager& inputs, float deltaTime)
{
    // D�placement joueur
    float movX = 0.f, movY = 0.f;
    Vector2 posPlayer = player->GetPosition(0.5f, 0.5f);
    Vector2 sizePlayer = player->GetSize();

    if (inputs.IsHeld(SDLK_z) && posPlayer.y - (sizePlayer.y / 2) > 0) movY -= 1.0f;
    else if (inputs.IsHeld(SDLK_z)) player->SetPosition(posPlayer.x, 0.0f + (sizePlayer.y / 2));
    if (inputs.IsHeld(SDLK_q) && posPlayer.x - (sizePlayer.x / 2) > 0) movX -= 1.0f;
    else if (inputs.IsHeld(SDLK_q)) player->SetPosition(0.0f + (sizePlayer.x / 2), posPlayer.y);
    if (inputs.IsHeld(SDLK_s) && posPlayer.y + (sizePlayer.y / 2) < HEIGHT - 1) movY += 1.0f;
    else if (inputs.IsHeld(SDLK_s)) player->SetPosition(posPlayer.x, HEIGHT - 1 - (sizePlayer.y / 2));
    if (inputs.IsHeld(SDLK_d) && posPlayer.x + (sizePlayer.x / 2) < WIDTH - 1) movX += 1.0f;
    else if (inputs.IsHeld(SDLK_d)) player->SetPosition(WIDTH - 1 - (sizePlayer.x / 2), posPlayer.y);

    // Normalisation du d�placement
    if (movX != 0 || movY != 0)
    {
        float length = std::sqrt(movX * movX + movY * movY);
        movX = (movX / length) * PLAYER_SPEED;
        movY = (movY / length) * PLAYER_SPEED;
        player->Move(movX * deltaTime, movY * deltaTime);
    }

    // Tir du joueur
    if (player->fire_cooldown > 0) player->fire_cooldown -= deltaTime;
    if (inputs.IsHeld(SDLK_SPACE) && player->fire_cooldown <= 0)
    {
        Projectile* bullet = new Projectile(renderer,
            "../../assets/sprites/bullets_sprite.png", // portion g�r�e dans Projectile
            90,
            posPlayer.x + 20,
            posPlayer.y,
            500.f,
            Projectile::PLAYER);  // MODIFI� : Ajoute l'owner
        bullets.push_back(bullet);
        player->fire_cooldown = 1.0f / FIRE_RATE;
    }

    // D�placement des ennemis vers la gauche
    for (auto& enemy : enemies)
    {
        enemy->Move(-enemy->move_speed * deltaTime, 0);

        // R�appara�t � droite si sort � gauche
        Vector2 posEnemy = enemy->GetPosition(0.5f, 0.5f);
        if (posEnemy.x < -50)
        {
            enemy->SetPosition(WIDTH + 50, posEnemy.y, 0.5f, 0.5f);
        }
    }

    // Tir des ennemis
    for (auto& enemy : enemies)
    {
        if (enemy->fire_cooldown > 0)
            enemy->fire_cooldown -= deltaTime;

        if (enemy->fire_cooldown <= 0)
        {
            Vector2 posEnemy = enemy->GetPosition(0.5f, 0.5f);  // D�FINITION ICI

            Projectile* bullet = new Projectile(renderer,
                "../../assets/sprites/bullets_sprite.png",
                90,
                posEnemy.x - 20,
                posEnemy.y,
                -500.f,
                Projectile::ENEMY);  // MODIFI� : Ajoute l'owner

            bullets.push_back(bullet);
            enemy->fire_cooldown = 1.0f;
        }
    }

    // Mise � jour des projectiles
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i]->Move(deltaTime);
        if (bullets[i]->IsOutOfBounds(WIDTH, HEIGHT))
        {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            continue;
        }
    }

    // NOUVEAU : V�rification des collisions
    CheckCollisions();
    // mise a jour background
	background->UpdateBackground(renderer, deltaTime);
}

void EntityManager::CheckCollisions()
{
    // Collision projectiles ennemis -> joueur
    for (int i = bullets.size() - 1; i >= 0; i--)
    {
        if (bullets[i]->owner == Projectile::ENEMY)
        {
            if (static_cast<Rectangle*>(bullets[i]->hitbox)->Intersects(static_cast<Rectangle*>(player->hitbox)))
            {
                std::cout << "TOUCHE ! PV avant: " << player->pv << std::endl;  // DEBUG
                player->TakeDamage(1);
                std::cout << "PV apres: " << player->pv << std::endl;  // DEBUG

                delete bullets[i];
                bullets.erase(bullets.begin() + i);

                if (!player->is_alive)
                {
                    std::cout << "GAME OVER!" << std::endl;
                }
                continue;
            }
        }

        // Collision projectiles joueur -> ennemis
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
                        delete enemies[j];
                        enemies.erase(enemies.begin() + j);
                    }
                    break;
                }
            }

            if (bulletDestroyed)
            {
                continue;
            }
        }
    }
}


Player* EntityManager::GetPlayer()
{
    return player;
}

std::vector<Enemy*> EntityManager::GetEnemies()
{
    
    return enemies;
}

std::vector<Projectile*> EntityManager::GetBullets()
{
    return bullets;
}

Background* EntityManager::GetBackground()
{
    return background;
}

void EntityManager::AddEnemy(Enemy* e)
{
     
}

void EntityManager::AddBullet(Projectile* b)
{
}

void EntityManager::RemoveEnemy(Enemy* e)
{
}

void EntityManager::RemoveBullet(Projectile* b)
{
}
