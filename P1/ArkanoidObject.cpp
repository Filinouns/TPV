#include "ArkanoidObject.h"

ArkanoidObject::ArkanoidObject(SDL_Renderer* r, Texture* text) : GameObject() {
	texture = text;
	renderer = r;
	active = true;
}

ArkanoidObject::~ArkanoidObject() {}

void ArkanoidObject::loadFromFile() {

}