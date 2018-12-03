#pragma once
#include "MovingObject.h"

class Game;

class Ball : public MovingObject {
public:
	Ball() {};
	Ball(SDL_Renderer* r, Texture* text, Game* g);
	virtual ~Ball();

	virtual void render();
	virtual void update();
	virtual void loadFromFile();
	virtual void saveToFile(ofstream& f);
	void respawn();

private:
	Game* game = nullptr;

	bool resp = false;

	Vector2D initVel = Vector2D(2, -2);
};