#pragma once

#include <vector>

#include <SDL.h>

#include "EntityManager.h"
class EntityManager;
enum Menu;

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>


#define WIDTH 1300
#define HEIGHT 800

#define TARGET_FPS 60
#define TARGET_DELTA_TIME 1.0f / TARGET_FPS

#define PLAYER_SPEED 300.0f
#define FIRE_RATE 5.0f
#define ENEMY_FIRE_RATE 2.0f
class ScreenManager
{

public:

    void DrawHealthBar(Player* player);
    SDL_Window* window;
    SDL_Renderer* renderer;

    ScreenManager();


    bool Init();
    // Permet de changer d��cran (menu, jeu, pause�)
    void Update(EntityManager& entities);
    SDL_Renderer* GetRenderer();
    SDL_Window* GetWindow();
};

