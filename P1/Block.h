#pragma once
#include "Texture.h"
#include "checkML.h"
#include "Vector2D.h"

class Block {
public:
	SDL_Renderer* renderer;

	Block() {};
	Block(SDL_Renderer* r, Texture* text, int color, int row, int col, float height, float width);
	virtual ~Block();
	int getY() { return pos.getY(); };
	int getX() { return pos.getX(); };
	int getRow() { return fila; }
	int getCol() { return columna; }
	uint getH() { return h; };
	uint getW() { return w; };

	void render();

	void setActive(bool a) { active = a; };
	bool getActive() { return active; }

protected:
	Texture* textura = nullptr;
	SDL_Rect destRect;

	Vector2D pos = Vector2D(0, 0);
	Vector2D vColor = Vector2D(0, 0);

	uint w, h;
	int color = 0;
	int fila = 0;
	int columna = 0;
	bool active;
};