#include "MovingObject.h"

MovingObject::MovingObject(SDL_Renderer* r, Texture* text) : ArkanoidObject(r, text) {
}

MovingObject::~MovingObject() {}

void MovingObject::loadFromFile(ifstream& f) {}