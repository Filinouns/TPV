#include "Reward.h"
#include "Game.h"

Reward::Reward(SDL_Renderer* r, Texture* text, int x, int y, int row, Game* g) : MovingObject(r, text) {
	fRow = row;
	fCol = 0;
	game = g;

	pos.setX(x);
	pos.setY(y);

	destRect.x = x;
	destRect.y = y;
	destRect.w = REWARD_W;
	destRect.h = REWARD_H;
	vel = initVel;
}

Reward::~Reward() {}

void Reward::render() {
	if (active) texture->renderFrame(destRect, fRow, fCol);
}

void Reward::update() {
}


