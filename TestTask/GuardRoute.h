#pragma once


#include "Utilities.h"

enum class GuardRouteType
{
	CIRCLE,
	ILINE,
	JLINE
};

class GuardRoute
{

public:

	GuardRoute(GuardRouteType type_);
	~GuardRoute();

	const iVector2& NextKeyPoint();

private:

	const iVector2 routeParams = { mapSize / 10, mapSize * 9 / 10 - 1 };

	GuardRouteType type;

	list<iVector2> keyPoints;

	list<iVector2>::const_iterator currentKeyPoint;

};

