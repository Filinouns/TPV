#pragma once
#include "Texture.h"
#include "checkML.h"
#include "Vector2D.h"
#include "Paddle.h"
//#include "Game.h"		//No funciona correctamente el programa si hacemos el puntero a juego

class Game;

class Ball {
public:
	SDL_Renderer* renderer;

	Ball() {};
	Ball(SDL_Renderer* r, Texture* text, Game* g);
	virtual ~Ball();

	virtual void render();
	virtual void update();
	void respawn();

	SDL_Rect getRect() { return destRect; }

private:
	Game* game = nullptr;
	Texture* texture = nullptr;
	SDL_Rect destRect;

	bool resp = false;

	Vector2D initVel = Vector2D(2, -2);
	
	Vector2D pos = Vector2D(0, 0);
	Vector2D vel;
	uint w, h;
};