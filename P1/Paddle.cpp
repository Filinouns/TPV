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

	//dirX = 1; // 1: se mueve en positivo		-1: se mueve en negativo
	//dirY = 0; // 0: no se mueve
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
	destRect.x = x;
}

bool Paddle::collides(const SDL_Rect& r, Vector2D& collVector) {
	bool hit = false;
	if (r.x > this->getX() - this->getW() && r.x < this->getX() + this->getW()) {
		if (r.y < this->getY() - this->getH() && r.y > this->getY() - 50) {
			hit = true;
			collVector = { 0, 1 };
			/*if (r.x - this->getX() < - 10) { //Izq
				collVector = { -1, 0 };
			}
			else if (r.x - this->getX() > 10) { //Der
				collVector = { 1, 0 };
			}
			else { //Medio
				collVector = { 0, 1 };
			}*/
		}
	}
	return hit;
}

void Paddle::handleEvents(SDL_Event event) {
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT: //Para salir con esc
			if (x > WALL_WIDTH) {
				x -= PADDLE_MOVE;
			}
			break;
		case SDLK_RIGHT:
			if (x < WIN_WIDTH - WALL_WIDTH - destRect.w) {
				x += PADDLE_MOVE;
			}
			break;
		default:
			break;
		}
	}
}