#pragma once

#include "Utilities.h"
#include "AffineRotation.h"


namespace
{
	enum class TransName
	{
		RX,
		RY,
		RZ,
		PZ
	};
}

class Isometric
{

public:

	~Isometric();

	static Isometric* Instance();

	Vector3 ToImaginary(const Vector3& point);
	Vector3 ToReal(const Vector3& point);

	void AddTransformation(TransName axis, float angle);

private:

	Isometric();
	Isometric(const Isometric& other);
	void operator = (const Isometric& other);

	static Isometric* instance;

	const Vector2 screenOffset = Vector2 { 512.0f, 384.0f };

	vector<AffineRotation*> transformations;

};

