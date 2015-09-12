#include "YRotation.h"


YRotation::YRotation(float angleDegrees) : AffineRotation(angleDegrees)
{
}

YRotation::~YRotation()
{
}

void YRotation::Rotate(Vector3& point) const
{
	Vector3 tmp = point;

	point.x = cos(-angleRadians) * tmp.x - sin(-angleRadians) * tmp.z;
	point.z = sin(-angleRadians) * tmp.x + cos(-angleRadians) * tmp.z;
}

void YRotation::ReverseRotate(Vector3& point) const
{
	Vector3 tmp = point;

	point.x = cos(-angleRadians) * tmp.x + sin(-angleRadians) * tmp.z;
	point.z = -sin(-angleRadians) * tmp.x + cos(-angleRadians) * tmp.z;
}

