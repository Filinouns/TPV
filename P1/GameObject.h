#pragma once
#include "checkML.h"
#include <list>
#include <fstream>

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handleEvents() = 0;
};