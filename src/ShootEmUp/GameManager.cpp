#include "GameManager.h"

void GameManager::InitGame()
{
	screens.Init();
	// init assets
	assets = AssetManager::GetInstance();
	assets->LoadAssets(screens.GetRenderer());
	// init entities
	entities.Init(screens.GetRenderer());
	// load first screen



	SDL_SetRenderDrawColor(screens.GetRenderer(), 255, 0, 0, 255);
}


void GameManager::GameLoop(bool& running)
{
	float deltaTime = 0;
	Uint64 start = SDL_GetTicks64();

	// inputs update
	inputs.Update();

	if (inputs.IsDown(SDLK_ESCAPE)) running = false;

	// entities update
	entities.Update(screens.GetRenderer(), inputs, TARGET_DELTA_TIME);

	// screen update
	screens.Update(entities);

	// Limitation FPS
	Uint64 end = SDL_GetTicks64();
	deltaTime = (end - start) / 1000.f;
	float diff = TARGET_DELTA_TIME - deltaTime;
	if (diff > 0) SDL_Delay(diff * 1000);

	
}

void GameManager::EndGame() {
	SDL_DestroyRenderer(screens.GetRenderer());
	SDL_DestroyWindow(screens.GetWindow());
	SDL_Quit();
}
