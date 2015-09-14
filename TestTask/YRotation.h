#pragma once

#include "AffineRotation.h"


class YRotation : public AffineRotation
{

public:

	YRotation(float angleDegrees);
	~YRotation() override;

	void Rotate(Vector3& point) const override;
	void ReverseRotate(Vector3& point) const override;

};

