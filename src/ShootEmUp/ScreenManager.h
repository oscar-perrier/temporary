#pragma once

#include <vector>

#include <SDL.h>

#include "EntityManager.h"
class EntityManager;

#include <SDL_image.h>
#include <iostream>


#define WIDTH 1000
#define HEIGHT 600

#define TARGET_FPS 60
#define TARGET_DELTA_TIME 1.0f / TARGET_FPS


class ScreenManager
{

public:

    void DrawHealthBar(Player* player);
    SDL_Window* window;
    SDL_Renderer* renderer;

    ScreenManager();


    bool Init();
    // Permet de changer d’écran (menu, jeu, pause…)
    void Update(EntityManager& entities);
    SDL_Renderer* GetRenderer();
    SDL_Window* GetWindow();
};

