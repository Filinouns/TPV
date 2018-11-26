#pragma once
#include "ArkanoidError.h"

class SDLError : public ArkanoidError {
public:
	SDLError(string error);
	virtual ~SDLError();

};