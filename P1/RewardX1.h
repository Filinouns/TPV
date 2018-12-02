#pragma once
#include "Reward.h"
class RewardX1 : public Reward {
public:
	RewardX1() {}
	RewardX1(SDL_Renderer* r, Texture* text, int x, int y, Game* g);

	virtual ~RewardX1();
};