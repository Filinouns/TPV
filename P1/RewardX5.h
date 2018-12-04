#pragma once
#include "Reward.h"

class RewardX5 : public Reward {
public:
	RewardX5() {}
	RewardX5(SDL_Renderer* r, Texture* text, int x, int y, Game* g);

	virtual ~RewardX5();
};