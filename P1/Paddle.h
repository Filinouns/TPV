#pragma once
#include "ArkanoidObject.h"

class Paddle : public ArkanoidObject {
public:
	Paddle() {};
	Paddle(SDL_Renderer* r, Texture* text);
	virtual ~Paddle();

	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event event);
	bool collides(const SDL_Rect& r, Vector2D& collVector); //Comprobacion de choque con la pelota
	//virtual void renderFrame() {}

protected:
	bool moveL, moveR;
	int speed = 0;

	//Game* game = nullptr; //Not needed in general
};