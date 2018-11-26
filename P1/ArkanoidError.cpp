#include "ArkanoidError.h"

ArkanoidError::ArkanoidError(string error) : logic_error(error) {

}

ArkanoidError::~ArkanoidError() {}