#pragma once
#include "ArkanoidObject.h"

class Block : public ArkanoidObject {
public:
	Block() {};
	Block(SDL_Renderer* r, Texture* text, int color, int row, int col, float height, float width);
	virtual ~Block();
	int getY() { return pos.getY(); };
	int getX() { return pos.getX(); };
	int getRow() { return fila; }
	int getCol() { return columna; }
	uint getH() { return h; };
	uint getW() { return w; };

	virtual void render();

	void setActive(bool a) { active = a; };
	bool getActive() { return active; }

protected:
	SDL_Rect destRect;

	Vector2D vColor = Vector2D(0, 0);

	uint w, h;
	int color = 0;
	int fila = 0;
	int columna = 0;
	bool active;
};