#pragma once
#include "ArkanoidError.h"

class FileNotFoundError : public ArkanoidError {
public:
	FileNotFoundError(const string& error) : ArkanoidError(error) {}
};