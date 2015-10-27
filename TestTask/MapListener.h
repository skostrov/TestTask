#pragma once


class MapListener
{

public:

	MapListener();
	virtual ~MapListener();

	virtual void OnMapChanged() = 0;

};

