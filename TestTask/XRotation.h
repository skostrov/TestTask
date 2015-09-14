#pragma once

#include "AffineRotation.h"


class XRotation : public AffineRotation
{

public:

	XRotation(float angleDegrees);
	~XRotation() override;

	void Rotate(Vector3& point) const override;
	void ReverseRotate(Vector3& point) const override;

};

