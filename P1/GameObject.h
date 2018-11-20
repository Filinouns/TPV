#pragma once
#include "checkML.h"

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

