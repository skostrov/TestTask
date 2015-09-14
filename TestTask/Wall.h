#pragma once

#include "Utilities.h"
#include "WallTile.h"
#include "TraversableMap.h"


class Wall : public SceneObject
{

public:

	Wall(TraversableMap* grid_, bool orient_, vector<int> cannonPos_, HTEXTURE safeTexture_, HTEXTURE dangerousTexture_);
	~Wall() override;

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	Vector3 GetRealCenter() const;

private:

	void InitiateWallTile(int index, HGE* hge);

	HTEXTURE safeTexture;
	HTEXTURE dangerousTexture;

	Vector3 realCenter;

	WallTile* wallGrid[mapSize];

	vector<int> cannonPos;

	TraversableMap* grid;

	bool orient;

};

