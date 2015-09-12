#pragma once

#include "AffineRotation.h"


class ZRotation : public AffineRotation
{

public:

	ZRotation(float angleDegrees);
	~ZRotation();

	void Rotate(Vector3& point) const override;
	void ReverseRotate(Vector3& point) const override;

};

