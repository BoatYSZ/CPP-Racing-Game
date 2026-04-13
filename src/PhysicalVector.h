#pragma once
class PhysicalVector
{
public:
	PhysicalVector(double direction, double magnitude);
	PhysicalVector& operator+=(double plus);
	PhysicalVector& operator+=(PhysicalVector& other);
	PhysicalVector& operator-();
	PhysicalVector operator*(double t) const;
	PhysicalVector& operator=(const PhysicalVector& other);
	double getX();
	double getY();

	double direction;
	double magnitude;
};

