#include "Isometric.h"
#include "XRotation.h"
#include "YRotation.h"
#include "ZRotation.h"
#include "ZProjection.h"


Isometric* Isometric::instance = nullptr;

Isometric::Isometric()
{
}

Isometric::~Isometric()
{
	for (auto& i : transformations)
	{
		delete i;
	}

	transformations.clear();

	delete instance;
}

Isometric* Isometric::Instance()
{
	if (!instance)
	{
		instance = new Isometric();

		instance->AddTransformation(TransName::RZ, -45.0f);
		instance->AddTransformation(TransName::RX, 60.0f);
		instance->AddTransformation(TransName::PZ, 60.0f);
	}

	return instance;
}

Vector3 Isometric::ToImaginary(const Vector3& point)
{
	Vector3 result = point;

	for (const auto& i : transformations)
	{
		i->Rotate(result);
	}

	result.x += screenOffset.x;
	result.y += screenOffset.y;

	return result;
}

Vector3 Isometric::ToReal(const Vector3& point)
{
	Vector3 result = point;

	result.x -= screenOffset.x;
	result.y -= screenOffset.y;

	for (auto i = transformations.crbegin(); i != transformations.crend(); ++i)
	{
		(*i)->ReverseRotate(result);
	}

	return result;
}

void Isometric::AddTransformation(TransName axis, float angle)
{
	switch (axis)
	{
	case TransName::RX:

		transformations.push_back(new XRotation(angle));

		break;

	case TransName::RY:

		transformations.push_back(new YRotation(angle));

		break;

	case TransName::RZ:

		transformations.push_back(new ZRotation(angle));

		break;

	case TransName::PZ:

		transformations.push_back(new ZProjection(angle));

		break;

	default:
		break;
	}
}

