#pragma once

#include "Utilities.h"
#include "Character.h"
#include "GuardRoute.h"


class Guard : public Character
{

public:

	Guard(TraversableMap* grid_, const iVector2& startPos, HTEXTURE texture, GuardRouteType routeType_);
	~Guard();

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void OccupyTile(const iVector2& index) override;
	void FreeTile(const iVector2& index) override;

private:

	GuardRoute route;

};

