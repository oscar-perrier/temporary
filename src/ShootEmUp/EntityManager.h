#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Upgrade.h"
#include "Background.h"
#include "Button.h"
#include "ScreenManager.h"
#include <SDL_ttf.h>
#include "InputManager.h"
#include <vector>

#define PLAYER_SPEED 300.0f

enum Menu;

class EntityManager
{
private:
    Player* player;
    Background* background;
    std::vector<Enemy*> enemies;
    std::vector<Projectile*> bullets;
    std::vector<Upgrade*> upgrades;
	Menu currentState;
	Button* startButton = nullptr;
	Button* quitButton = nullptr;
	Button* menuButton = nullptr;
	Button* retryButton = nullptr;
	std::vector<Button*> levelButtons;

    void CheckCollisions(SDL_Renderer* renderer);
    void CheckUpgradeCollisions();
    Enemy* FindNearestEnemy(const Vector2& position);

public:
    ~EntityManager();

    void Init(SDL_Renderer* renderer, Menu menu);
    void Update(SDL_Renderer* renderer, InputManager& inputs, float deltaTime);

    Player* GetPlayer();
    std::vector<Enemy*> GetEnemies();
    std::vector<Projectile*> GetBullets();
    std::vector<Upgrade*> GetUpgrades();
    Background* GetBackground();

    void AddEnemy(Enemy* e);
    void AddBullet(Projectile* b);
    void AddUpgrade(Upgrade* u);
    void RemoveEnemy(Enemy* e);
    void RemoveBullet(Projectile* b);

	
	Button* GetStartButton();
	Button* GetQuitButton();
	Button* GetRetryButton();
	Button* GetMenuButton();
	Menu CheckState();
	void SetState(Menu state);
};