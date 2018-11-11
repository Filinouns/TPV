#include "Vector2D.h"

Vector2D::Vector2D() : x(), y() {}

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

Vector2D::~Vector2D() {}

double Vector2D::getX() const {	return x; }

double Vector2D::getY() const {	return y; }

void Vector2D::normalice() {
	double lenght = sqrt( x * x + y * y );

	if (lenght > 0) {
		x = x / lenght;
		y = y / lenght;
	}
}

Vector2D Vector2D::operator+(const Vector2D& v) const {
	Vector2D r;
	r.x = x + v.x;
	r.y = y + v.y;
	return r;
}

Vector2D Vector2D::operator*(double d) const {
	Vector2D r;
	r.x = x * d;
	r.y = y * d;
	return r;
}

double Vector2D::operator*(const Vector2D& d) const {
	return d.x * x + d.y * y;
}

Vector2D Vector2D::op(const Vector2D & d) const {
	Vector2D r;
	r.x = x + d.x;
	r.y = y + d.y;
	return r;
}

Vector2D Vector2D::operator-(const Vector2D& v) const {
	Vector2D r;
	r.x = x - v.x;
	r.y = y - v.y;
	return r;
}