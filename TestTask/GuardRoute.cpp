#include "GuardRoute.h"


GuardRoute::GuardRoute(GuardRouteType type_) : type(type_)
{
	switch (type_)
	{

	case GuardRouteType::CIRCLE:

		for (int k = routeParams.i; k <= routeParams.j; ++k)
		{
			keyPoints.push_back({ routeParams.i, k });
		}

		for (int k = routeParams.i; k <= routeParams.j; ++k)
		{
			keyPoints.push_back({ k, routeParams.j });
		}

		for (int k = routeParams.j; k >= routeParams.i; --k)
		{
			keyPoints.push_back({ routeParams.j, k });
		}

		for (int k = routeParams.j; k >= routeParams.i; --k)
		{
			keyPoints.push_back({ k, routeParams.i });
		}

		break;

	case GuardRouteType::ILINE:

		for (int k = routeParams.i; k <= routeParams.j; ++k)
		{
			keyPoints.push_back({ mapSize / 2, k });
		}

		break;

	case GuardRouteType::JLINE:

		for (int k = routeParams.i; k <= routeParams.j; ++k)
		{
			keyPoints.push_back({ k, mapSize / 2 });
		}

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

GuardRouteType GuardRoute::GetType()
{
	return type;
}

