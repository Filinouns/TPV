#pragma once
#include "Texture.h"
#include "checkML.h"
#include "Vector2D.h"

const int WALL_WIDTH = 40;


class Wall
{
public:
	SDL_Renderer* renderer;

	Wall() {};
	Wall(SDL_Renderer* r, Texture* text, Vector2D position, bool roof);
	virtual ~Wall();

	void render();

protected:
	Vector2D pos = Vector2D(0, 0);
	uint h = 0;
	uint w = 0;

	SDL_Rect destRect;
	Texture* texture = nullptr;
};