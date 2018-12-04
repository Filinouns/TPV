#pragma once
#include "ArkanoidObject.h"

class MovingObject : public ArkanoidObject {
public:
	MovingObject() {};
	MovingObject(SDL_Renderer* r, Texture* text);
	virtual ~MovingObject();

	virtual void loadFromFile(ifstream& f);
protected:
	Vector2D vel;
};

