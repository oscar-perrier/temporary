#pragma once

#include <map>
#include <SDL.h>
#include <vector>

class AssetManager
{
	static AssetManager* instance;

public:
	std::map<const char*, SDL_Texture*> textures;
	std::map<const char*, std::vector<SDL_Texture*>> animatedTextures;



	static AssetManager* GetInstance();
	
	void LoadAssets(SDL_Renderer* renderer);

	SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* path);
	std::vector<SDL_Texture*> LoadAnimatedTexture(SDL_Renderer* renderer, const char* path);
};


