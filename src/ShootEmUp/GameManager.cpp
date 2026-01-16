#include "GameManager.h"

void GameManager::InitGame()
{
	TTF_Init();
	menuState = Menu::MainMenu;
	screens.Init();
	// init assets
	assets = AssetManager::GetInstance();
	assets->LoadAssets(screens.GetRenderer());
	// init entities
	entities.Init(screens.GetRenderer(), menuState);
	// load first screen
	levels.LoadLevel("../../levels/Level1.txt");

	SDL_SetRenderDrawColor(screens.GetRenderer(), 255, 0, 0, 255);
}

void GameManager::GameLoop(bool& running)
{
	float deltaTime = 0;
	Uint64 start = SDL_GetTicks64();


	// inputs update
	inputs.Update();

	switch (menuState) {
	case Menu::MainMenu:
		MainMenu(running);
		break;
	case Menu::LevelSelection:
		LevelSelection(running);
		break;
	case Menu::PlayingLevel:
		PlayingLevel(running);
		break;
	case Menu::Defeat:
		Defeat(running);
		break;
	case Menu::Quit:
		running = false;
		return;
	}

	if (inputs.IsDown(SDLK_ESCAPE)) running = false;
	
	entities.Update(screens.GetRenderer(), inputs, TARGET_DELTA_TIME);

	// screen update
	screens.Update(entities);


	// Limitation FPS
	Uint64 end = SDL_GetTicks64();
	deltaTime = (end - start) / 1000.f;
	float diff = TARGET_DELTA_TIME - deltaTime;
	if (diff > 0) SDL_Delay(diff * 1000);

	
}

void GameManager::MainMenu(bool& running) {
	Menu state = entities.CheckState();
	if (state != menuState) {
		menuState = state;
		return;
	}
	if (inputs.IsDown(SDLK_ESCAPE)) running = false;
}

void GameManager::LevelSelection(bool& running) {
	Menu state = entities.CheckState();
	if (state != menuState) {
		menuState = state;
		return;
	}
	if (inputs.IsDown(SDLK_ESCAPE)) running = false;
}

void GameManager::PlayingLevel(bool& running) {
	Menu state = entities.CheckState();
	if (state != menuState) {
		menuState = state;
		return;
	}
	// entities update
	bool readState = levels.ReadLevel(entities, screens.GetRenderer(), TARGET_DELTA_TIME);
	if (entities.GetEnemies().empty() && readState) {
		menuState = Menu::MainMenu;
		entities.SetState(menuState);
		return;
	}
	if (inputs.IsDown(SDLK_ESCAPE)) running = false;
}

void GameManager::Defeat(bool& running) {
	Menu state = entities.CheckState();
	if (state != menuState) {
		menuState = state;
		return;
	}
	if (levels.currentReadLength != 0) levels.currentReadLength = 0;
	if (inputs.IsDown(SDLK_ESCAPE)) running = false;
}

void GameManager::EndGame() {
	delete assets;
	SDL_DestroyRenderer(screens.GetRenderer());
	SDL_DestroyWindow(screens.GetWindow());
	SDL_Quit();
	TTF_Quit();
}