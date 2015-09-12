#include "AffineRotation.h"


AffineRotation::AffineRotation(float angleDegrees)
{
	angleRadians = DegToRad(angleDegrees);
}


AffineRotation::~AffineRotation()
{
}
