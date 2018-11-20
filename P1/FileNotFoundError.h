#pragma once
#include "ArkanoidError.h"
class FileNotFoundError :
	public ArkanoidError
{
public:
	FileNotFoundError();
	virtual ~FileNotFoundError();
};

