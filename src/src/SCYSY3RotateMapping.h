#pragma once
#include "ImagePixelMapping.h"

class SCYSY3RotateMapping : public ImagePixelMapping
{
public:
	SCYSY3RotateMapping(double r)
		: rotation(r)
	{
	}

	virtual bool mapCoordinates(double& x, double& y, const SimpleImage& image) override
	{
		x -= image.getWidth() / 2;
		y -= image.getHeight() / 2;
		double dAngle = atan2(y , x);
		double hyp = ::sqrt(x * x + y * y);
		dAngle += (double)rotation;
		x = hyp * ::cos(dAngle);
		y = hyp * ::sin(dAngle);
		x += image.getWidth() / 2;
		y += image.getHeight() / 2;
		if (x < 0) return false;
		if (y < 0) return false;
		if (x >= (image.getWidth() - 0.5)) return false;
		if (y >= (image.getHeight() - 0.5)) return false;

		return true;
	}

	double getRotation() { return rotation; }
	void setRotation(double r) { rotation = r; }

protected:
	double rotation;
};

