#pragma once
#include "MovingObject.h"

class Game;

class Ball : public MovingObject {
public:
	Ball() {};
	Ball(SDL_Renderer* r, Texture* text, Game* g);
	virtual ~Ball();

	virtual void update();
	virtual void loadFromFile();
	virtual void saveToFile(fstream& f);
	void respawn();

private:
	Game* game = nullptr;

	int velLimit = 2;
	bool resp = false;

	Vector2D initVel = Vector2D(velLimit, -velLimit);
};