#pragma once
#include "Reward.h"

class RewardX2 : public Reward
{
public:
	RewardX2() {};
	RewardX2(SDL_Renderer* r, Texture* text, int x, int y, int row, Game* g); 
	virtual ~RewardX2();

	virtual void action();
	virtual void update();
	
};

