#include "Ball.h"
#include "Game.h"

Ball::Ball(SDL_Renderer* r, Texture* text, Game* g) : MovingObject(r, text) {
	game = g;

	vel = initVel;

	h = BALL_SIZE;
	w = BALL_SIZE;

	pos = Vector2D(((WIN_HEIGHT / 3) * 2), (WIN_WIDTH / 2));
	x = pos.getX();
	y = pos.getY();

	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;
}

Ball::~Ball() {}

void Ball::respawn() {
	resp = true;
	pos = Vector2D(((WIN_HEIGHT / 3) * 2), (WIN_WIDTH / 2));
	x = pos.getX();
	y = pos.getY();

	destRect.x = x;
	destRect.y = y;

	vel = initVel;
}

void Ball::update() {
	//actualizar x e y (vel)4
	Vector2D collVector;
	Vector2D prevPos = pos;
	
	if (game->collidesBall(destRect, vel, collVector)) {
		if (!resp) {
			vel = vel - (collVector * (2 * (vel*collVector)));
			pos = prevPos + vel;
			x = pos.getX();
			y = pos.getY();
			//Controlador de velocidad
			if (vel.getX() > velLimit)			vel.setX(velLimit);
			else if (vel.getX() < -velLimit)	vel.setX(-velLimit);
			if (vel.getY() > velLimit)			vel.setY(velLimit);
			else if (vel.getY() < -velLimit)	vel.setY(-velLimit);
		} else resp = false;
	} else {
		pos = prevPos + vel;
		x = pos.getX();
		y = pos.getY();
	}

	destRect.x = x;
	destRect.y = y;
}

void Ball::saveToFile(fstream& f) {
	f << vel.getX() << " " << vel.getY() << " ";
	ArkanoidObject::saveToFile(f);
}

void Ball::loadFromFile(ifstream& f) {
	int vx, vy;
	f >> vx >> vy;
	vel = Vector2D(vx, vy);
	velLimit = vy;
	ArkanoidObject::loadFromFile(f);
}