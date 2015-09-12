#pragma once

#include "AffineRotation.h"


class XRotation : public AffineRotation
{

public:

	XRotation(float angleDegrees);
	~XRotation();

	void Rotate(Vector3& point) const override;
	void ReverseRotate(Vector3& point) const override;

};

