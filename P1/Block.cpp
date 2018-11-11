#include "Block.h"
#include "Wall.h"

Block::Block(SDL_Renderer* r, Texture * text, int c, int row, int col, float height, float width) {
	renderer = r;
	textura = text;
	color = c;
	fila = row;
	columna = col;
	h = height;
	w = width;

	active = true;

	pos = Vector2D(columna  * w + WALL_WIDTH, fila  * h + WALL_WIDTH);

	destRect.x = pos.getX(); //Se pone al reves porque sino se escriben giradas, ya que queremos la fila(pos.X) para la posicion "y" del bloque en la escena
	destRect.y = pos.getY(); //y la columna(pos.Y) para la posicion "x" del bloque en la escena.
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
	if (active) {
		textura->renderFrame(destRect, vColor.getX(), vColor.getY());
	}
}