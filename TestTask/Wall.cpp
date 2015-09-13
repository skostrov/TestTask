#include "Wall.h"


Wall::Wall(TraversableMap* grid_, bool orient_, HTEXTURE safeTexture_, HTEXTURE dangerousTexture_) : grid(grid_), orient(orient_), safeTexture(safeTexture_), dangerousTexture(dangerousTexture_)
{
}

Wall::~Wall()
{
	for (auto& i : wallGrid)
	{
		delete i;
	}
}

void Wall::Initiate(HGE* hge, const Vector3& center)
{
	float tileWidth = grid->GetTileByIndex({ 0, 0 }).Size() * 2;
	float tileHeight = grid->GetTileByIndex({ 0, 0 }).Size() * 2;

	if (orient)
	{
		realCenter.x = center.x + tileWidth * mapSize;//TileInitHelp::halfSize;
		realCenter.y = center.y;
	}
	else
	{
		realCenter.x = center.x;
		realCenter.y = center.y - tileWidth * mapSize;//TileInitHelp::halfSize;
	}
	realCenter.z = center.z - tileHeight;

	for (int i = 0; i < mapSize; ++i)
	{
		InitiateWallTile(i, hge);
	}
}

void Wall::HandleEvent(HGE* hge, hgeInputEvent* inputEvent)
{
}

void Wall::Update(float dt)
{
}

void Wall::Render(HGE* hge)
{
	for (auto& i : wallGrid)
	{
		i->Render(hge);
	}
}

Vector3 Wall::RealCenter()
{
	return realCenter;
}

bool Wall::Orient()
{
	return orient;
}

void Wall::InitiateWallTile(int index, HGE* hge)
{
	wallGrid[index] = new WallTile();
	wallGrid[index]->SetOrient(orient);
	float tileWidth = wallGrid[index]->Width();
	float tileHeight = wallGrid[index]->Height();

	Vector3 tileCenter;
	int	offSet = TileInitHelp::QuadrantBasedOffset(index);
	int quadrant = (index >= TileInitHelp::halfSize) ? 1 : -1;

	if (orient)
	{
		tileCenter.x += 2 * tileWidth * TileInitHelp::halfSize;
		tileCenter.y += quadrant * tileWidth * (2 * offSet + 1);

	}
	else
	{
		tileCenter.x += quadrant * tileWidth * (2 * offSet + 1);
		tileCenter.y -= 2 * tileWidth * TileInitHelp::halfSize;
	}

	//tileCenter.z -= tileHeight;

	wallGrid[index]->SetOrient(orient);
	wallGrid[index]->Initiate(hge, tileCenter);

	if (wallGrid[index]->IsSafe())
	{
		wallGrid[index]->SetTexture(safeTexture);
	}
	else
	{
		wallGrid[index]->SetTexture(dangerousTexture);
	}
}

