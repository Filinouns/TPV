#include "Wall.h"
#include "Game.h"

Wall::Wall(SDL_Renderer * r, Texture* text, Vector2D position, bool roof) {
	renderer = r;
	texture = text;
	pos = position;

	destRect.x = pos.getX();
	destRect.y = pos.getY(); 
	if (!roof) {
		h = WIN_WIDTH;
		w = WALL_WIDTH;
	} else {
		h = WALL_WIDTH;
		w = WIN_WIDTH;
	}
	destRect.h = h;
	destRect.w = w;
}

Wall::~Wall() {} 

void Wall::render() {
	texture->renderFrame(destRect, 0, 0);
}