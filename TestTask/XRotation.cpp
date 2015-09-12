#include "XRotation.h"


XRotation::XRotation(float angleDegrees) : AffineRotation(angleDegrees)
{
}

XRotation::~XRotation()
{
}

void XRotation::Rotate(Vector3& point) const
{
	Vector3 tmp = point;

	point.y = cos(angleRadians) * tmp.y - sin(angleRadians) * tmp.z;
	point.z = sin(angleRadians) * tmp.y + cos(angleRadians) * tmp.z;
}

void XRotation::ReverseRotate(Vector3& point) const
{
	Vector3 tmp = point;

	point.y = cos(angleRadians) * tmp.y + sin(angleRadians) * tmp.z;
	point.z = -sin(angleRadians) * tmp.y + cos(angleRadians) * tmp.z;
}

