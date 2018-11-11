#include "Ball.h"
#include "Game.h"
#include "Paddle.h"

Ball::Ball(SDL_Renderer* r, Texture* text, Game* g) {
	renderer = r;
	texture = text;
	game = g;

	vel = initVel;

	h = BALL_SIZE;
	w = BALL_SIZE;

	pos = Vector2D(((WIN_HEIGHT / 3) * 2), (WIN_WIDTH / 2));
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.w = w;
	destRect.h = h;
}

Ball::~Ball() {}

void Ball::render() {
	texture->renderFrame(destRect, 0, 0);
}

void Ball::respawn() {
	resp = true;
	pos = Vector2D(((WIN_HEIGHT / 3) * 2), (WIN_WIDTH / 2));
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	vel = initVel;
}

void Ball::update() {
	//actualizar x e y (vel)4
	Vector2D collVector;
	Vector2D prevPos = pos;
	
	if (game->collides(destRect, vel, collVector)) {
		if (!resp) {
			vel = vel - (collVector * (2 * (vel*collVector)));
			pos = prevPos + vel;
			destRect.x = pos.getX();
			destRect.y = pos.getY();
			//Controlador de velocidad
			if (vel.getX() > 2)			vel.setX(2);
			else if (vel.getX() < -2)	vel.setX(-2);
			if (vel.getY() > 2)			vel.setY(2);
			else if (vel.getY() < -2)	vel.setY(-2);
		} else resp = false;
	} else {
		pos = prevPos + vel;
		destRect.x = pos.getX();
		destRect.y = pos.getY();
	}
}