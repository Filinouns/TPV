#pragma once
#include "Reward.h"

class RewardX4 : public Reward {
public:
	RewardX4() {}
	RewardX4(SDL_Renderer* r, Texture* text, int x, int y, Game* g);

	virtual ~RewardX4();
};