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

class Isometric													// Класс-синглтон, изпользующийся для инкапсуляции
{																// функиций перевода координат из реальных (realCenter
																// у класса Tile и т.д.) в экранные/воображаемые
																// (imCenter).
																//
																// Воображаемые координаты являются двухмерными
																// и используются непосредственно при отрисовке объектов.
																// Благодаря этим координатам создается изометрическое
																// изображение на плоскости.
																// 
																// Реальные координаты трехмерны. Направление осей Ox и Oy
																// в этих координатах совпадает с направлением экранных осей
																// (Ox - вправо, Oy - вниз). Ось Oz (мнимая) уходит вглубь
																// экрана. Ox, Oy и Oz образуют левую тройку веторов.
																// Изначально у всех объектов сцены задается центр в реальных
																// координатах, потом в методе Initiate или конструкторе объекта
																// вычисляются экранные/воображаемые координаты. Вычисление
																// происходит как последовательное применение аффинных преобразований
																// поворота и проекции на плоскость экрана из массива transformations

public:

	~Isometric();

	static Isometric* Instance();

	Vector3 ToImaginary(const Vector3& point);
	Vector3 ToReal(const Vector3& point);

	void AddTransformation(TransName axis, float angle);

	void Release();

private:

	Isometric();
	Isometric(const Isometric& other);
	void operator = (const Isometric& other);

	static Isometric* instance;

	const Vector2 screenOffset = Vector2 { 512.0f, 384.0f };

	vector<AffineRotation*> transformations;

};

