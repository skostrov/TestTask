#pragma once

#include "Utilities.h"
#include "WallTile.h"
#include "TraversableMap.h"
#include "Projectile.h"


class Wall : public SceneObject
{

public:

	Wall(TraversableMap* grid_, bool orient_, HTEXTURE safeTexture_, HTEXTURE dangerousTexture_);
	~Wall();

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	Vector3 RealCenter();

	bool Orient();

private:

	void InitiateWallTile(int index, HGE* hge);

	HTEXTURE safeTexture;
	HTEXTURE dangerousTexture;

	Vector3 realCenter;

	WallTile* wallGrid[mapSize];

	list<Projectile*> projectiles;

	TraversableMap* grid;

	bool orient;

};

