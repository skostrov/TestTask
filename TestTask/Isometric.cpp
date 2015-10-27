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
}

Isometric* Isometric::Instance()
{
	if (!instance)
	{
		instance = new Isometric();

		instance->AddTransformation(TransName::RZ, -45.0f);			// Для того, чтобы в игре использовался вид сверху
		instance->AddTransformation(TransName::RX, 60.0f);			// необходимо закомментировать эти строки (они
		instance->AddTransformation(TransName::PZ, 60.0f);			// отвечают за поворот вокруг оси Oz на -45 градусов,
	}																// поворот вокруг оси Ox на 60 и проекцию на плоскость
																	// экрана соответственно).
	return instance;
}

Vector3 Isometric::ToImaginary(const Vector3& point)
{
	Vector3 result = point;

	for (const auto& i : transformations)
	{
		i->Rotate(result);						// При переходе из реальных координат в экранные
	}											// преобразования применяются в прямом порядке.
												// В методе Rotate происходит умножение на вектора
	result.x += screenOffset.x;					// point на матрицу поворота.
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
		(*i)->ReverseRotate(result);		// При переходе из экранных в реальные координаты
	}										// все преобразования применяются в обратном порядке.
											// В методе ReverseRotate происходит умножение 
	return result;							// на матрицу, обратную к матрице поворота.
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

void Isometric::Release()
{
	for (auto& i : transformations)
	{
		delete i;
	}

	transformations.clear();
}

