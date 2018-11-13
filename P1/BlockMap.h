#pragma once
#include "ArkanoidObject.h"
#include "Block.h"
#include <iostream>
#include <fstream>

enum BlocksColor {Empty, Blue, Green, Red, Yellow, Black, Purple};

class BlockMap : public ArkanoidObject{
public:
	BlockMap(SDL_Renderer* r, Texture* text);
	virtual ~BlockMap();

	void load(const string& filename);
	virtual void render();
	int getNumBlocks() { return numBlocks; }
	Block* collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector);
	Block* blockAt(const Vector2D& p);
	void ballHitsBlock(Block* b);

	Texture* texture;
	SDL_Renderer* renderer;
protected:
	Block*** map = nullptr;

	int col = 0;
	int row = 0;
	int color;
	int numBlocks = 0;

	float height = 0, width = 0;
};

