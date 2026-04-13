#include "header.h"
#include "PhysicalVector.h"
#include <cmath>

PhysicalVector::PhysicalVector(double direction, double magnitude)
	:magnitude(magnitude)
	, direction(direction)
{

}
PhysicalVector& PhysicalVector::operator+=(double plus) {
	magnitude += plus;
	return *this;
}
PhysicalVector& PhysicalVector::operator+=(PhysicalVector& other) {
	double x1 = magnitude * cos(direction) + other.magnitude * cos(other.direction);
	double y1 = magnitude * sin(direction) + other.magnitude * sin(other.direction);
	magnitude = sqrt(x1 * x1 + y1 * y1);
	direction = atan2(y1, x1);
	return *this;
}
PhysicalVector& PhysicalVector::operator-(){
	direction += M_PI;
	return *this;
}

PhysicalVector PhysicalVector::operator*(double t) const {
	double newMagnitude = magnitude * t;
	double newDirection = direction;

	if (t < 0) {
		newDirection += M_PI;
		newDirection = fmod(newDirection, 2 * M_PI);
		newMagnitude = newMagnitude * (-1);
	}
	return PhysicalVector(newDirection, newMagnitude);
}

PhysicalVector& PhysicalVector::operator=(const PhysicalVector& other) {
	if (this != &other) {
		direction = other.direction;
		magnitude = other.magnitude;
	}
	return *this;
}
double PhysicalVector::getX() {
	return magnitude * cos(direction);
}
double PhysicalVector::getY() {
	return magnitude * sin(direction);
}