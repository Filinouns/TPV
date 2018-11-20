#pragma once
#include "ArkanoidObject.h"

class Block : public ArkanoidObject {
public:
	Block() {};
	Block(SDL_Renderer* r, Texture* text, int color, int row, int col, float height, float width);
	virtual ~Block();
	int getRow() { return fila; }
	int getCol() { return columna; }
	int getX() { return x; }
	int getY() { return y; }
	int getH() { return h; }
	int getW() { return w; }

	virtual void render();

	void setActive(bool a) { active = a; };
	bool getActive() { return active; }

protected:
	Vector2D vColor = Vector2D(0, 0);

	int color = 0;
	int fila = 0;
	int columna = 0;
	bool active;
};