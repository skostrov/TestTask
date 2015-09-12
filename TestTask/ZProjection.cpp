#include "ZProjection.h"


ZProjection::ZProjection(float angleDegrees) : AffineRotation(angleDegrees)
{
}


ZProjection::~ZProjection()
{
}

void ZProjection::Rotate(Vector3& point) const
{
	point.z = 0;
}

void ZProjection::ReverseRotate(Vector3& point) const
{
	point.z = 2 * fabs(sin(angleRadians)) * point.y;
}

