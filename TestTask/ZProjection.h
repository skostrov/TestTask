#pragma once

#include "AffineRotation.h"


class ZProjection : public AffineRotation
{

public:

	ZProjection(float angleDegrees);
	~ZProjection();

	void Rotate(Vector3& point) const override;
	void ReverseRotate(Vector3& point) const override;

};

