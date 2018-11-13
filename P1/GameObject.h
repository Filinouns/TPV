#pragma once
#include "Vector2D.h"
#include "checkML.h"
#include "Game.h"

class GameObject {
public:
	GameObject() {};
	virtual ~GameObject();

	virtual void render() {};
	virtual void update() {};
	virtual void handleEvents() {};

protected:

private:

};

