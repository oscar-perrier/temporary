#pragma once

#include "InputManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Background.h"
#include "ScreenManager.h"
#include <vector>

class EntityManager
{
	Player* player;
	std::vector<Enemy*> enemies;
	std::vector<Projectile*> bullets;
	Background* background;

public:
	~EntityManager();
	void Init(SDL_Renderer* renderer);
	void Update(SDL_Renderer* renderer, InputManager& inputs, float deltaTime);
	void CheckCollisions();
	Player* GetPlayer();
	std::vector<Enemy*> GetEnemies();
	std::vector<Projectile*> GetBullets();
	Background* GetBackground();
	void AddEnemy(Enemy* e);
	void AddBullet(Projectile* b);
	void RemoveEnemy(Enemy* e);
	void RemoveBullet(Projectile* b);
};

