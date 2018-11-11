#pragma once
#include <vector>
#include "checkML.h"

class Vector2D {
public:
	Vector2D();
	Vector2D(double x, double y);
	~Vector2D();

	double getX() const;
	double getY() const;
	void setX(double ox) { x = ox; }
	void setY(double oy) { y = oy; }
	void normalice();
	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator-(const Vector2D& v) const;
	Vector2D operator*(double d) const;
	double operator*(const Vector2D& d) const;
	Vector2D op (const Vector2D& d) const;

private:
	double x, y;
};