#pragma once

#include "Utilities.h"


class MapListener
{

public:

	MapListener();
	virtual ~MapListener();

	virtual void OnMapChanged() = 0;

};

