#pragma once
#include "ArkanoidObject.h"

class Wall : public ArkanoidObject {
public:
	Wall(SDL_Renderer* r, Texture* text, Vector2D position, bool roof);
	virtual ~Wall();

	virtual void render();

protected:
	Vector2D pos = Vector2D(0, 0);
	uint h = 0;
	uint w = 0;

	SDL_Rect destRect;
};