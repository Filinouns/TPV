#include "Block.h"
#include "Game.h"

Block::Block(SDL_Renderer* r, Texture * text, int c, int row, int col, float height, float width) : ArkanoidObject (r, text) {
	color = c;
	fila = row;
	columna = col;
	h = height;
	w = width;

	active = true;

	pos = Vector2D(columna  * w + WALL_WIDTH, fila  * h + WALL_WIDTH);

	x = pos.getX();
	y = pos.getY();

	destRect.x = x;
	destRect.y = y;
	destRect.h = h;
	destRect.w = w;

	switch (color) {
	case 1:
		vColor = Vector2D(0, 0);
		break;
	case 2:
		vColor = Vector2D(0, 1);
		break;
	case 3:
		vColor = Vector2D(0, 2);
		break;
	case 4:
		vColor = Vector2D(1, 0);
		break;
	case 5:
		vColor = Vector2D(1, 1);
		break;
	case 6:
		vColor = Vector2D(1, 2);
		break;
	default:
		vColor = Vector2D(0, 0);
		break;
	}
}

Block::~Block(){}

void Block::render() {
	if (active) texture->renderFrame(destRect, vColor.getX(), vColor.getY());
}