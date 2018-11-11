#include "Paddle.h"
#include "Game.h"

Paddle::Paddle(SDL_Renderer* r, Texture* text) {
	renderer = r;
	texture = text;

	x = WIN_WIDTH / 2 - texture->getW() / 2;
	y = WIN_HEIGHT - 100;
	h = texture->getH();
	w = texture->getW();

	destRect.h = destRect.w = h;
	destRect.x = x;
	destRect.y = y;

	moveL = false;
	moveR = false;
}

Paddle::~Paddle() {}

void Paddle::render() {
	destRect.w = w;
	destRect.h = h;
	destRect.y = y;
	destRect.x = x;
	texture->renderFrame(destRect, 0, 0);
}

void Paddle::update() {
	destRect.x += speed;
	x = destRect.x;
	if (x < WALL_WIDTH + 5 || (x + w) > WIN_WIDTH - WALL_WIDTH - 10) speed = 0;
}

bool Paddle::collides(const SDL_Rect& r, Vector2D& collVector) {
	float size = destRect.w/3;
	bool hit = false;
	if (r.x >= destRect.x && r.x <= destRect.x + destRect.w) {
		if (r.y > destRect.y - destRect.h && r.y < destRect.y) {
			hit = true;
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
	}
	return hit;
}

void Paddle::handleEvents(SDL_Event event) {
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (x > WALL_WIDTH) {
				speed = -3;
			}
			break;
		case SDLK_RIGHT:
			if (x < WIN_WIDTH - WALL_WIDTH - destRect.w) {
				speed = 3;
			}
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		case (SDLK_RIGHT || SDLK_LEFT):
			speed = 0;
			break;
	}
}