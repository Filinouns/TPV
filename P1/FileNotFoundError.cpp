#include "FileNotFoundError.h"

FileNotFoundError::FileNotFoundError(string error) : ArkanoidError(error) {

}

FileNotFoundError::~FileNotFoundError() {}
