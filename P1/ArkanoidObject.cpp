#include "ArkanoidObject.h"

ArkanoidObject::ArkanoidObject(SDL_Renderer* r, Texture* text) : GameObject() {
	texture = text;
	renderer = r;
}

ArkanoidObject::~ArkanoidObject() {}

void ArkanoidObject::loadFromFile() {

}

void ArkanoidObject::saveToFile() {

}

SDL_Rect ArkanoidObject::getRect() {
	return destRect;
}