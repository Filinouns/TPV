#include "ArkanoidObject.h"

ArkanoidObject::ArkanoidObject(SDL_Renderer* r, Texture* text) : GameObject() {
	texture = text;
	renderer = r;
	active = true;
}

ArkanoidObject::~ArkanoidObject() {}

void ArkanoidObject::render() {
	if(active) texture->renderFrame(destRect, 0, 0);
}

void ArkanoidObject::saveToFile(fstream& f) {
	f << destRect.x << " " << destRect.y << endl;
}

void ArkanoidObject::loadFromFile(ifstream& f) {
	f >> destRect.x >> destRect.y;
	x = destRect.x;
	y = destRect.y;
	pos.setX(x);
	pos.setY(y);
}