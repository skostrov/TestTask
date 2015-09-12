#pragma once

#include "Utilities.h"


class AffineRotation
{

public:

	AffineRotation(float angleDegrees);
	virtual ~AffineRotation();

	virtual void Rotate(Vector3& point) const = 0;
	virtual void ReverseRotate(Vector3& point) const = 0;

protected:

	float angleRadians;

};

