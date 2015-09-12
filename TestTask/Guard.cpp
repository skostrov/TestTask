#include "Guard.h"


Guard::Guard(TraversableMap* grid_, const iVector2& startPos, HTEXTURE texture, GuardRouteType routeType_) : Character(grid_, startPos, texture), route(routeType_)
{
}


Guard::~Guard()
{
}

void Guard::Initiate(HGE* hge, const Vector3& center)
{
	Character::Initiate(hge, center);
}

void Guard::HandleEvent(HGE* hge, hgeInputEvent* inputEvent)
{
	if ((inputEvent->type == INPUT_MBUTTONDOWN) && (inputEvent->key == HGEK_RBUTTON))
	{
		if (!currentPath.empty())
		{
			destinationPos = *currentPath.rbegin();
		}

		currentPath.clear();

		vector<void*> foundPath;
		int result = FindPath(foundPath);

		if (result == micropather::MicroPather::SOLVED)
		{
			SetFoundPathAsCurrent(foundPath);
		}
	}
}

void Guard::Update(float dt)
{
	if (IsMoving())
	{
		Move(dt);
	}
	else
	{
		if (!currentPath.empty())
		{
			nextPos = *currentPath.begin();
			currentPath.erase(currentPath.begin());
			OccupyTile(nextPos);
			Move(dt);
		}
		else
		{
			destinationPos = route.NextKeyPoint();

			vector<void*> foundPath;
			int result = FindPath(foundPath);

			if (result == micropather::MicroPather::SOLVED)
			{
				SetFoundPathAsCurrent(foundPath);
			}
		}
	}
}

void Guard::OccupyTile(const iVector2& index)
{
	grid->GetTileByIndex(index).SetOccupiedByGuard();
}

void Guard::FreeTile(const iVector2& index)
{
	grid->GetTileByIndex(index).SetFreeOfGuard();
}

