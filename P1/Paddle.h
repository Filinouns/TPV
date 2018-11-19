#pragma once
#include "MovingObject.h"

class Paddle : public MovingObject {
public:
	Paddle(SDL_Renderer* r, Texture* text);
	virtual ~Paddle();

	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event event);
	bool collides(const SDL_Rect& r, Vector2D& collVector); //Comprobacion de choque con la pelota

protected:
	bool moveL, moveR;
};