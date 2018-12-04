#pragma once
#include "ArkanoidObject.h"
#include "Block.h"
#include <iostream>
#include <fstream>

enum BlocksColor {Empty, Blue, Green, Red, Yellow, Black, Purple};

class BlockMap : public ArkanoidObject {
public:
	BlockMap(SDL_Renderer* r, Texture* text);
	virtual ~BlockMap();
	virtual void render();
	virtual void loadFromFile(ifstream& in);
	virtual void saveToFile(fstream& f);

	void load(const string& filename);
	int getNumBlocks() { return numBlocks; }
	Block* collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector);
	Block* blockAt(const Vector2D& p);
	void ballHitsBlock(Block* b);

	int numRow() { return row; }

protected:
	Block*** map = nullptr;

	int col = 0;
	int row = 0;
	int color;
	int numBlocks = 0;
};