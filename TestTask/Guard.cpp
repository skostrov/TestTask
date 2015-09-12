#include "Guard.h"


Guard::Guard(TraversableMap* grid_, const iVector2& startPos, HTEXTURE texture) : Character(grid_, startPos, texture)
{
}


Guard::~Guard()
{
}

void Guard::OccupyTile()
{
	grid->GetTileByIndex(currentPos).SetOccupiedByGuard();
}

