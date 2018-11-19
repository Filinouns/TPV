#pragma once
#include "GameObject.h"
#include "Texture.h"

#include "Wall.h"
#include "Paddle.h"
#include "Block.h"
#include "Ball.h"
#include "BlockMap.h"

class ArkanoidObject : public GameObject {
public:
	ArkanoidObject() {};
	ArkanoidObject(SDL_Renderer* r, Texture* text);
	virtual ~ArkanoidObject();

	virtual void loadFromFile();
	virtual void saveToFile();
	virtual SDL_Rect getRect();

protected:
	Vector2D pos;

	float w, h;
	float x = 0;
	float y = 0;
	SDL_Rect destRect;

	Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;

private:

};