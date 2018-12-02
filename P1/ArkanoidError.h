#pragma once
#include <stdexcept>

using namespace std;

class ArkanoidError : public logic_error {
public:
	ArkanoidError(const string& error) : logic_error (error) {}
};