#pragma once
#include "MovingObject.h"

class Game;

class Paddle : public MovingObject {
public:
	Paddle(SDL_Renderer* r, Texture* text, Game* g);
	virtual ~Paddle();

	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event event);
	bool collides(const SDL_Rect& r);
	bool collidesBall(const SDL_Rect& r, Vector2D& collVector); //Comprobacion de choque con la pelota
	bool collidesReward(const SDL_Rect& r);
	void powerUp(int type);

protected:
	bool moveL, moveR;
	Game *game = nullptr;
};