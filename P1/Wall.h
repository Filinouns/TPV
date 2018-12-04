#pragma once
#include "ArkanoidObject.h"

class Wall : public ArkanoidObject {
public:
	Wall(SDL_Renderer* r, Texture* text, Vector2D position, bool roof);
	virtual ~Wall();
};