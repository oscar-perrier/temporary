#include "Button.h"

Button::Button(SDL_Renderer* renderer, const char* text, int posX, int posY, int w, int h)
{
	Sans = TTF_OpenFont("../../assets/fonts/Sans.ttf", 48);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text, Black);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	Message_rect = { posX, posY, w, h };
	SDL_FreeSurface(surfaceMessage);
	hitbox = new Rectangle(w, h-80);
	hitbox->SetPosition(posX, posY+45,0.f,0.f);
}

void Button::SetPosition(float x, float y, float anchorX, float anchorY) {
	Message_rect.x = x;
	Message_rect.y = y;
	hitbox->SetPosition(x, y + 45, 0.f, 0.f);
}

Vector2 Button::GetPosition(float anchorX, float anchorY)
{
	return Vector2(); // placeholder
}

void Button::Move(float x, float y)
{
	// placeholder
}

void Button::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	hitbox->Draw(renderer);
}
