#include "Reward.h"
#include "Game.h"

Reward::Reward(SDL_Renderer* r, Texture* text, int x, int y, int row) : MovingObject(r, text) {
	fRow = row;
	fCol = 0;

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
	texture->renderFrame(destRect, fRow, fCol);
}

void Reward::update() {
	cont++;
	if (cont > 10) {
		fCol++;
		cont = 0;
	}
	if (fCol > 7) fCol = 0;

	pos = pos + vel;
	x = pos.getX();
	y = pos.getY();
	destRect.x = x;
	destRect.y = y;
}
