#include "LevelManager.h"
#include "ScreenManager.h"
#include <fstream>
#include <chrono>

void LevelManager::LoadLevel(const char* path)
{
    std::ifstream my_file(path);
    if (my_file.is_open())
    {
        std::string line;

        // 1. Lire toutes les lignes
        while (std::getline(my_file, line))
        {
            lines.push_back(line);
        }
        my_file.close();
    }

    // 2. Trouver la longueur max
    maxLength = 0;
    currentReadLength = 0;
    read_next = 0;
    for (const auto& l : lines)
    {
        if (l.length() > maxLength)
            maxLength = l.length();
    }
}

bool LevelManager::ReadLevel(EntityManager& entities, SDL_Renderer* renderer, float deltaTime) {

    if (currentReadLength >= maxLength) return true;
    read_next += READ_SPEED * deltaTime;
    if (read_next >= 2.0f) {
        for (size_t row = 0; row < lines.size(); row++)
        {
            if (currentReadLength < lines[row].length())
            {
                char c = lines[row][currentReadLength];
                Enemy* e = nullptr;

                switch (c)
                {
                case 'E': // Ennemi normal
                    e = new Enemy(renderer, ENEMY_NORMAL);
                    e->SetPosition(WIDTH + 50, HEIGHT / lines.size() * row + 23);
                    entities.AddEnemy(e);
                    break;

                case 'O': // Obstacle (ne tire pas)
                    e = new Enemy(renderer, ENEMY_OBSTACLE);
                    e->SetPosition(WIDTH + 50, HEIGHT / lines.size() * row + 23);
                    entities.AddEnemy(e);
                    break;

                case 'T': // Tank (lent mais tire vite)
                    e = new Enemy(renderer, ENEMY_TANK);
                    e->SetPosition(WIDTH + 50, HEIGHT / lines.size() * row + 23);
                    entities.AddEnemy(e);
                    break;

                case 'U': // Upgrade
                {
                    UpgradeType type = (UpgradeType)(rand() % 4);
                    Upgrade* upgrade = new Upgrade(renderer, type, WIDTH + 50, HEIGHT / 10 * row + 23);
                    entities.AddUpgrade(upgrade);
                    break;
                }
                case 'B': // Boss
                    e = new Enemy(renderer, ENEMY_BOSS);
                    e->SetPosition(WIDTH + 150, HEIGHT / lines.size() * row + 23, 0.5f, 0.5f);
                    entities.AddEnemy(e);
                    break;
                }
            }
        }
        currentReadLength++;
        read_next = 0;
    }
    return false;
}