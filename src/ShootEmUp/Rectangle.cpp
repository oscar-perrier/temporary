#include "Rectangle.h"

#include <SDL.h>
#include "Projectile.h"
#include "CustomMath.h"

Rectangle::Rectangle(int w, int h) : Geometry(w, h)
{
}

void Rectangle::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { posX, posY, width, height };

	SDL_RenderDrawRect(renderer, &rect);
}
bool Rectangle::Intersects(const Geometry* other) const
{
    // Cast en Rectangle pour acc�der aux coordonn�es
    const Rectangle* otherRect = dynamic_cast<const Rectangle*>(other);
    if (!otherRect) return false;

    float left1 = posX;
    float right1 = posX + width;
    float top1 = posY;
    float bottom1 = posY + height;

    float left2 = otherRect->posX;
    float right2 = otherRect->posX + otherRect->width;
    float top2 = otherRect->posY;
    float bottom2 = otherRect->posY + otherRect->height;

    return !(right1 < left2 || left1 > right2 || bottom1 < top2 || top1 > bottom2);
}