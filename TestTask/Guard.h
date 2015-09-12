#pragma once

#include "Utilities.h"
#include "Character.h"


class Guard : public Character
{

public:

	Guard(TraversableMap* grid_, const iVector2& startPos, HTEXTURE texture);
	~Guard();

	virtual void OccupyTile() override;

};

