#include "Wall.h"
#include "Game.h"

Wall::Wall(SDL_Renderer * r, Texture* text, Vector2D position, bool roof) : ArkanoidObject(r, text) {
	x = position.getX();
	y = position.getY();

	if (!roof) {
		h = WIN_WIDTH;
		w = WALL_WIDTH;
	} else {
		h = WALL_WIDTH;
		w = WIN_WIDTH;
	}
	destRect.x = x;
	destRect.y = y;
	destRect.h = h;
	destRect.w = w;
}

Wall::~Wall() {} 