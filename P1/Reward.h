#pragma once
#include "MovingObject.h"

class Reward : public MovingObject {
public:
	Reward() {};
	Reward(SDL_Renderer* r, Texture* text, int x, int y, int row);
	virtual ~Reward();

	virtual void render();
	virtual void update();

protected:
	int cont = 0;
	int fRow, fCol;
	Vector2D initVel = Vector2D(0, 1);
};

