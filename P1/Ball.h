#pragma once
#include "MovingObject.h"
#include "Paddle.h"
//#include "Game.h"		//No funciona correctamente el programa si hacemos el puntero a juego

class Game;

class Ball : public MovingObject {
public:
	Ball() {};
	Ball(SDL_Renderer* r, Texture* text, Game* g);
	virtual ~Ball();

	virtual void render();
	virtual void update();
	void respawn();

private:
	Game* game = nullptr;

	bool resp = false;

	Vector2D initVel = Vector2D(2, -2);
};