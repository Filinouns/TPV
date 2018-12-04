#include "RewardX5.h"

RewardX5::RewardX5(SDL_Renderer* r, Texture* text, int x, int y, Game* g) : Reward(r, text, x, y, g) {
	fRow = 2;
	type = 4;
}

RewardX5::~RewardX5() {}