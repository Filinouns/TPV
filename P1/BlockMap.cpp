#include "BlockMap.h"

BlockMap::BlockMap(SDL_Renderer* r, Texture* text) : ArkanoidObject (r, text) {}

BlockMap::~BlockMap() { //Eliminamos la memoria dinamica
	if (map != nullptr) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				delete map[i][j];
				map[i][j] = nullptr;
			}
			delete[] map[i];
			map[i] = nullptr;
		}

		delete[] map;
		map = nullptr;
	}
}

void BlockMap::load(const string& filename) {
	ifstream in(filename);
	in >> row >> col;

	map = new Block**[row];
	for (int i = 0; i < row; i++) {
		map[i] = new Block*[col];
	}

	h = (WIN_HEIGHT / 2) / row;
	w = WIN_WIDTH / col - ((2*WALL_WIDTH) / col);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			in >> color;
			if (color != 0) {
				map[i][j] = new Block(renderer, texture, color, i, j, h, w);
				numBlocks++;
			}
			else map[i][j] = nullptr;
		}
	}
}

void BlockMap::render() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (map[i][j] != nullptr) map[i][j]->render();
		}
	}
}

/* Dados el rectángulo y vector de dirección de la pelota, devuelve un puntero al
bloque con el que ésta colisiona (nullptr si no colisiona con nadie) y el
vector normal perpendicular a la superficie de colisión.
*/
Block* BlockMap::collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector) {
	Vector2D p0 = { static_cast<double>(ballRect.x), static_cast<double>(ballRect.y) }; // top-left
	Vector2D p1 = { static_cast<double>(ballRect.x) + static_cast<double>(ballRect.w), static_cast<double>(ballRect.y) }; // top-right
	Vector2D p2 = { static_cast<double>(ballRect.x), static_cast<double>(ballRect.y) + static_cast<double>(ballRect.h) }; // bottom-left
	Vector2D p3 = { static_cast<double>(ballRect.x) + static_cast<double>(ballRect.w), 
					static_cast<double>(ballRect.y) + static_cast<double>(ballRect.h) }; // bottom-right
	Block* b = nullptr;
	SDL_Rect rect = b->getRect();
	if (ballVel.getX() < 0 && ballVel.getY() < 0) {
		if ((b = blockAt(p0))) {
			if ((rect.y + rect.h - p0.getY()) <= (rect.x + rect.w - p0.getX()))
				collVector = { 0,1 }; // Borde inferior mas cerca de p0
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p1))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p2))) collVector = { 1,0 };
	}
	else if (ballVel.getX() >= 0 && ballVel.getY() < 0) {
		if ((b = blockAt(p1))) {
			if (((rect.y + rect.h - p1.getY()) <= (p1.getX() - rect.x)) || ballVel.getX() == 0)
				collVector = { 0,1 }; // Borde inferior mas cerca de p1
			else
				collVector = { -1,0 }; // Borde izqdo mas cerca de p1
		}
		else if ((b = blockAt(p0))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p3))) collVector = { -1,0 };
	}
	else if (ballVel.getX() > 0 && ballVel.getY() > 0) {
		if ((b = blockAt(p3))) {
			if (((p3.getY() - rect.y) <= (p3.getX() - rect.x))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p3
			else
				collVector = { -1,0 }; // Borde dcho mas cerca de p3
		}
		else if ((b = blockAt(p2))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p1))) collVector = { -1,0 };
	}
	else if (ballVel.getX() < 0 && ballVel.getY() > 0) {
		if ((b = blockAt(p2))) {
			if (((p2.getY() - rect.y) <= (rect.x + rect.w - p2.getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p2
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p3))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p0))) collVector = { 1,0 };
	}
	return b;
}


/*  Devuelve el puntero al bloque del mapa de bloques al que pertenece el punto p.
En caso de no haber bloque en ese punto (incluido el caso de que p esté fuera
del espacio del mapa) devuelve nullptr.
*/
Block* BlockMap::blockAt(const Vector2D& p) {
	int f, c;
	Block* b = nullptr;
	f = (p.getY() - WALL_WIDTH) / h;
	c = (p.getX() - WALL_WIDTH) / w;
	if ((f >= 0 && f < row) && (c >= 0 && c < col)) {
		b = map[f][c];
	}
	return b;
}

void BlockMap::ballHitsBlock(Block * b) {
	map[b->getRow()][b->getCol()]->setActive(false);
	numBlocks--;
}