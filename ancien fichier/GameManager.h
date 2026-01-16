#pragma once

#include "AssetManager.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "SoundManager.h"
#include "LevelManager.h"

enum Menu {
	MainMenu,
	LevelSelection,
	PlayingLevel,
	Defeat,
	Quit
};

class GameManager
{
	AssetManager* assets;
	EntityManager entities;
	InputManager inputs;
	ScreenManager screens;
	SoundManager sounds;
	LevelManager levels;
	Menu menuState;

public:

	void GameLoop(bool& running);

	void MainMenu(bool& running);

	void LevelSelection(bool& running);

	void PlayingLevel(bool& running);

	void Defeat(bool& running);

	void InitGame();

	void EndGame();

};

