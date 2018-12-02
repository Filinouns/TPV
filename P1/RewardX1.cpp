#include "RewardX1.h"

RewardX1::RewardX1(SDL_Renderer* r, Texture* text, int x, int y, Game* g) : Reward(r, text, x, y, g) {
	fRow = 1;
	type = 0;
}

RewardX1::~RewardX1() {}