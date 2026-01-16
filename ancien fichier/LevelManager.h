#pragma once
#include <vector>
#include <string>
#include "EntityManager.h"

#define READ_SPEED 1.0f

class LevelManager
{
public:
	std::vector<std::string> lines;
	int maxLength;
	int currentReadLength;
	float read_next;

	void LoadLevel(const char* path);
	bool ReadLevel(EntityManager& entities, SDL_Renderer* renderer, float deltaTime);
};

