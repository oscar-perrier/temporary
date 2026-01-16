#pragma once

#include <SDL.h>
#include <iostream>
#include <map>

class InputManager
{
	struct KeyState {
		bool isDown;
		bool isHeld;
		bool isUp;
	};

	struct MouseState {
		bool leftClick;
		bool rightClick;
		bool middleClick;
		int posX;
		int posY;
	};

	KeyState keyStates[SDL_NUM_SCANCODES];

public:
	static InputManager* GetInstance()
	{
		static InputManager instance;
		return &instance;
	}

	void Update() {
				// Reset key states
		for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
			KeyState& state = keyStates[i];
			if (state.isDown) 
				state.isHeld = true;
			if (state.isUp) 
				state.isHeld = false;
			state.isDown = false;
			state.isUp = false;
		}

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
			{
				if (event.key.repeat)
					break;
				keyStates[event.key.keysym.scancode].isDown = true;
				break;
			}
			case SDL_KEYUP:
			{
				keyStates[event.key.keysym.scancode].isUp = true;
				break;
			}
			}
		}
	}

	bool IsDown(SDL_KeyCode key) {
		SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
		return keyStates[scancode].isDown;
	}

	bool IsHeld(SDL_KeyCode key) {
		SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
		return keyStates[scancode].isHeld;
	}

	bool IsUp(SDL_KeyCode key) {
		SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
		return keyStates[scancode].isUp;
	}
};


