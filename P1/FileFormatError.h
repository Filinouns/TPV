#pragma once
#include "ArkanoidError.h"

class FileFormatError : public ArkanoidError {
public:
	FileFormatError(string error);
	virtual ~FileFormatError();
};

