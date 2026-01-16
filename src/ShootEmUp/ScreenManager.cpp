#include "ScreenManager.h"
#include "GameManager.h"

ScreenManager::ScreenManager()
    : renderer(nullptr), window(nullptr)
{
}

bool ScreenManager::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        std::cout << "Error SDL2 Initialization : " << SDL_GetError();
        return 1;
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    window = SDL_CreateWindow("SPACE MESS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (!window)
    {
        std::cout << "Error window creation";
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Error renderer creation";
        return 1;
    }
}

void ScreenManager::Update(EntityManager& entities)
{
    // Rendu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // background
    entities.GetBackground()->Draw(renderer);

    // parallax elements
    entities.GetBackground()->PlanetsDraw(renderer);

    // upgrades
    for (auto& u : entities.GetUpgrades()) u->Draw(renderer);

    // bullets
    for (auto& b : entities.GetBullets()) b->Draw(renderer);

    // enemies
    for (auto& e : entities.GetEnemies()) e->Draw(renderer);

    if (entities.CheckState() == MainMenu) entities.GetStartButton()->Draw(renderer);
    if (entities.CheckState() == MainMenu) entities.GetQuitButton()->Draw(renderer);
    if (entities.CheckState() == Defeat) entities.GetRetryButton()->Draw(renderer);
    if (entities.CheckState() == Defeat) entities.GetMenuButton()->Draw(renderer);

    //player
    entities.GetPlayer()->Draw(renderer);

    // Affiche les PV
    DrawHealthBar(entities.GetPlayer());

    SDL_RenderPresent(renderer);
}

SDL_Renderer* ScreenManager::GetRenderer()
{
    return renderer;
}

SDL_Window* ScreenManager::GetWindow()
{
    return window;
}

void ScreenManager::DrawHealthBar(Player* player)
{
    // Dessine les coeurs/PV en haut à gauche
    int heartSize = 30;
    int spacing = 10;
    int startX = 20;
    int startY = 20;

    for (int i = 0; i < player->GetMaxPV(); i++)
    {
        SDL_Rect heartRect = { startX + i * (heartSize + spacing), startY, heartSize, heartSize };

        if (i < player->GetPV())
        {
            // Coeur plein (rouge vif)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &heartRect);
        }
        else
        {
            // Coeur vide (contour gris)
            SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
            SDL_RenderDrawRect(renderer, &heartRect);
        }

        // Bordure blanche autour de chaque coeur
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &heartRect);
    }

    // Affiche les upgrades actifs
    int iconSize = 25;
    int iconStartX = 20;
    int iconStartY = startY + heartSize + 15;

    if (player->has_homing_missiles)
    {
        SDL_Rect iconRect = { iconStartX, iconStartY, iconSize, iconSize };
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange
        SDL_RenderFillRect(renderer, &iconRect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &iconRect);
        iconStartX += iconSize + 5;
    }

    if (player->has_shield && player->shield_timer > 0)
    {
        SDL_Rect iconRect = { iconStartX, iconStartY, iconSize, iconSize };
        SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255); // Bleu
        SDL_RenderFillRect(renderer, &iconRect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &iconRect);
        iconStartX += iconSize + 5;
    }

    if (player->fire_rate > player->original_fire_rate * 1.5f)
    {
        SDL_Rect iconRect = { iconStartX, iconStartY, iconSize, iconSize };
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
        SDL_RenderFillRect(renderer, &iconRect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &iconRect);
    }

}
