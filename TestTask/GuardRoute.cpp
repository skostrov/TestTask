#include "GuardRoute.h"


GuardRoute::GuardRoute(GuardRouteType type_) : type(type_)
{
	switch (type_)
	{

	case GuardRouteType::CIRCLE:

		keyPoints.push_back({ routeParams.i, routeParams.i });
		keyPoints.push_back({ routeParams.i, routeParams.j });
		keyPoints.push_back({ routeParams.j, routeParams.j });
		keyPoints.push_back({ routeParams.j, routeParams.i });

		break;

	case GuardRouteType::ILINE:

		keyPoints.push_back({ mapSize / 2, routeParams.i });
		keyPoints.push_back({ mapSize / 2, routeParams.j });

		break;

	case GuardRouteType::JLINE:

		keyPoints.push_back({ routeParams.i, mapSize / 2 });
		keyPoints.push_back({ routeParams.j, mapSize / 2 });

		break;
	}

	currentKeyPoint = keyPoints.cbegin();
}

GuardRoute::~GuardRoute()
{
}

iVector2 GuardRoute::NextKeyPoint()
{
	iVector2 result;

	if (currentKeyPoint == keyPoints.cend())
	{
		currentKeyPoint = keyPoints.cbegin();
	}

	result = *currentKeyPoint;
	currentKeyPoint++;

	return result;
}

