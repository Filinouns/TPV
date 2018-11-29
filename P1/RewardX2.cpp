#include "RewardX2.h"
#include "Game.h"



RewardX2::RewardX2(SDL_Renderer* r, Texture* text, int x, int y, int row, Game* g) : Reward(r, text, x,  y,  row,  g) {
	fRow = 2;
}


RewardX2::~RewardX2(){}

void RewardX2::action() {
	//no consigo acceder al rect de paddle!!
}

void RewardX2::update() {
	if (game->collidesReward(destRect))
		action();

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
	if (game->collidesReward(destRect) || pos.getY() > WIN_HEIGHT) active = false;
}
