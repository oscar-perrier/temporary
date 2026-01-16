#pragma once

#include "AssetManager.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "SoundManager.h"

class GameManager
{
	AssetManager* assets;
	EntityManager entities;
	InputManager inputs;
	ScreenManager screens;
	SoundManager sounds;


public:

	void GameLoop(bool& running);

	void InitGame();

	void EndGame();

};

