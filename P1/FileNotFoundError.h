#pragma once
#include "ArkanoidError.h"
class FileNotFoundError : public ArkanoidError {
public:
	FileNotFoundError(string error);
	virtual ~FileNotFoundError();
};

