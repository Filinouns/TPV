#include "RewardX4.h"

RewardX4::RewardX4(SDL_Renderer* r, Texture* text, int x, int y, Game* g) : Reward(r, text, x, y, g) {
	fRow = 0;
	type = 3;
}

RewardX4::~RewardX4() {}