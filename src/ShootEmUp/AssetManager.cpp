#include "AssetManager.h"

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <filesystem>
namespace fs = std::filesystem;


AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new AssetManager();
	}
	return instance;
}


void AssetManager::LoadAssets(SDL_Renderer* renderer)
{
	LoadTexture(renderer, "../../assets/background/png/background_blue.png");
	//LoadTexture(renderer, "../../assets/spaceship_sprite.png");
	//LoadTexture(renderer, "../../assets/UI_sprite.png");
	//LoadTexture(renderer, "../../assets/spaceship_enemy.png");

	//LoadTexture(renderer, "../../assets/bullets_sprite.png");
	//LoadTexture(renderer, "../../assets/bonus_sprite.png");
	//LoadTexture(renderer, "../../assets/background.gif");

	const char* path = "../../assets/sprites/";
	for (const auto& entry : fs::directory_iterator(path))
		LoadTexture(renderer, entry.path().string().c_str());

	const char* path2 = "../../assets/background/gif/";
	for (const auto& entry : fs::directory_iterator(path2)) {
		//std::cout << entry.path() << std::endl;
		LoadAnimatedTexture(renderer, entry.path().string().c_str());
	}
}

SDL_Texture* AssetManager::LoadTexture(SDL_Renderer* renderer, const char* path)
{
	auto it = textures.find(path);

	if (it != textures.end()) {
		return it->second;
	}

	SDL_Surface* surface = IMG_Load(path);

	if (!surface) {
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	if (!texture) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	textures[path] = texture;

	return texture;
}

std::vector<SDL_Texture*> AssetManager::LoadAnimatedTexture(SDL_Renderer* renderer, const char* path)
{
	//auto it = animatedTextures.find(path);

	//if (it != animatedTextures.end()) {
	//	return it->second;
	//}

	IMG_Animation* animation = IMG_LoadAnimation(path);

	if (!animation) {
		std::cout << "Failed to load animation: " << path << std::endl;
		return {};
	}

	std::vector<SDL_Texture*> frames;
	for (int i = 0; i < animation->count; i++) {
		SDL_Texture* frame = SDL_CreateTextureFromSurface(renderer, animation->frames[i]);
		if (!frame) {
			std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		}
		frames.push_back(frame);
	}

	//delete animation;

	animatedTextures.push_back(frames);

	return frames;
}