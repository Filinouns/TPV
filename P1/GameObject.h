#pragma once
#include "checkML.h"
#include <list>

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	virtual void render() {};
	virtual void update() {};
	virtual void handleEvents() {};

protected:

private:

};

