#include "Reward.h"
#include "Game.h"

Reward::Reward(SDL_Renderer* r, Texture* text, int x, int y, Game* g) : MovingObject(r, text) {
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
	cont++;
	if (cont > 10) {
		fCol++;
		cont = 0;
	}
	if (fCol > 7) fCol = 0;

	//Posicion
	pos = pos + vel;
	x = pos.getX();
	y = pos.getY();
	destRect.x = x;
	destRect.y = y;

	// Colision/Destruccion
	action();
}

void Reward::action() {
	if (game->collidesReward(destRect)) {
		active = false;
		game->powerUp(type);
	}
	else if (pos.getY() > WIN_HEIGHT) {
		active = false;
	}
}

void Reward::loadFromFile(ifstream& f) {
	f >> type;
	ArkanoidObject::loadFromFile(f);
}

void Reward::saveToFile(fstream& f) {
	f << type << " ";
	ArkanoidObject::saveToFile(f);
}