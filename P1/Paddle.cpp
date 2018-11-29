#include "Paddle.h"
#include "Game.h"


Paddle::Paddle(SDL_Renderer* r, Texture* text) : MovingObject(r, text) {
	x = WIN_WIDTH / 2 - texture->getW() / 2;
	y = WIN_HEIGHT - 100;
	h = texture->getH();
	w = texture->getW();

	destRect.h = h;
	destRect.w = w;
	destRect.x = x;
	destRect.y = y;

	moveL = false;
	moveR = false;
}

Paddle::~Paddle() {}

void Paddle::render() {
	texture->renderFrame(destRect, 0, 0);
}

void Paddle::update() {
	destRect.x += vel.getX();
	x = destRect.x;
	if (x < WALL_WIDTH + 5 || (x + w) > WIN_WIDTH - WALL_WIDTH - 10) vel.setX(0);
}

bool Paddle::collides(const SDL_Rect& r) {
	bool hit = false;
	if (r.x >= destRect.x && r.x <= destRect.x + destRect.w) {
		if (r.y > destRect.y - destRect.h && r.y < destRect.y) {
			hit = true;
		}
	}
	return hit;
}

bool Paddle::collidesReward(const SDL_Rect& r) {
	bool hit = collides(r);
	return hit;
}

bool Paddle::collidesBall(const SDL_Rect& r, Vector2D& collVector) {
	bool hit = collides(r);
	if (hit) {
		float size = destRect.w / 3;
		collVector = { 0, 1 };
		/*float precision = r.x - destRect.x;
		if (precision <= destRect.w) {
			if (precision > 2 * size) { //Lado der
				collVector = { 1, 1 };
			} else if (precision > size) { //Medio
				collVector = { 0, 1 };
			} else { //Lado izq
				collVector = { -1, 1 };
			}
		}*/
	}
	return hit;
}

void Paddle::handleEvents(SDL_Event event) {
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (x > WALL_WIDTH) {
				vel.setX(-3);
			}
			break;
		case SDLK_RIGHT:
			if (x < WIN_WIDTH - WALL_WIDTH - destRect.w) {
				vel.setX(3);
			}
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		case (SDLK_RIGHT || SDLK_LEFT):
			vel.setX(0);
			break;
	}
}