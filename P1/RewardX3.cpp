#include "RewardX3.h"

RewardX3::RewardX3(SDL_Renderer* r, Texture* text, int x, int y, Game* g) : Reward(r, text, x, y, g) {
	fRow = 4;
	type = 2;
}

RewardX3::~RewardX3() {}