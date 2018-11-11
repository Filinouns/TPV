#pragma once
#include "Texture.h"
#include "checkML.h"
#include "Vector2D.h"

class Paddle {
	static const int ANIMATION_RATE = 100;
	static const int SPEED = 20;

public:
	SDL_Renderer* renderer;

	Paddle() {};
	Paddle(SDL_Renderer* r, Texture* text);
	virtual ~Paddle();
	int getX() { return x; }
	int getY() { return y; }
	int getW() { return w; }
	int getH() { return h; }

	void update();
	void render();
	void handleEvents(SDL_Event event);
	bool collides(const SDL_Rect& r, Vector2D& collVector);
	//virtual void renderFrame() {}

protected:
	uint w = 0;
	uint h = 0;
	uint x = 0;
	uint y = 0;

	//int dirX = 0;
	//int dirY = 0;

	SDL_Rect destRect;
	Texture* texture = nullptr;
	//Game* game = nullptr; //Not needed in general
};

