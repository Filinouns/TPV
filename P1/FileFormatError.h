#pragma once
#include "ArkanoidError.h"
class FileFormatError :
	public ArkanoidError
{
public:
	FileFormatError();
	virtual ~FileFormatError();
};

