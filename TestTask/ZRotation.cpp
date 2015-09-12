#include "ZRotation.h"


ZRotation::ZRotation(float angleDegrees) : AffineRotation(angleDegrees)
{
}

ZRotation::~ZRotation()
{
}

void ZRotation::Rotate(Vector3& point) const
{
	Vector3 tmp = point;

	point.x = cos(angleRadians) * tmp.x - sin(angleRadians) * tmp.y;
	point.y = sin(angleRadians) * tmp.x + cos(angleRadians) * tmp.y;
}

void ZRotation::ReverseRotate(Vector3& point) const
{
	Vector3 tmp = point;

	point.x = cos(angleRadians) * tmp.x + sin(angleRadians) * tmp.y;
	point.y = -sin(angleRadians) * tmp.x + cos(angleRadians) * tmp.y;
}

