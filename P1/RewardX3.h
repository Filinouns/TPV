#pragma once
#include "Reward.h"
class RewardX3 : public Reward
{
public:
	RewardX3() {}
	RewardX3(SDL_Renderer* r, Texture* text, int x, int y, Game* g);

	virtual ~RewardX3();
};

