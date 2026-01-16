#pragma once
#include "Player.h"

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#define WIDTH 1000
#define HEIGHT 600

#define TARGET_FPS 60
#define TARGET_DELTA_TIME 1.0f / TARGET_FPS

class EntityManager;

class ScreenManager
{
    SDL_Window* window;
    SDL_Renderer* m_renderer;

public:
    ScreenManager();

    bool Init();
    void DrawHealthBar(Player* player);
    // Permet de changer d’écran (menu, jeu, pause…)
    void Update(EntityManager& entities);
    SDL_Renderer* GetRenderer();
    SDL_Window* GetWindow();
};

