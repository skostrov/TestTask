#include "Map.h"
#include "HgeManager.h"


namespace TileInitHelp
{
	const int halfSize = mapSize / 2;

	int QuadrantBasedOffset(int index)
	{
		if (index >= halfSize)
		{
			return index - halfSize;
		}
		else
		{
			return halfSize - index - 1;
		}
	}
}

Map::Map(HTEXTURE texture) : tileTexture(texture)
{
}

Map::~Map()
{
}

void Map::Initiate(HGE* hge, const Vector3& center)
{
	realCenter = { center.x, center.y };

	for (int i = 0; i < mapSize; ++i)
	{
		for (int j = 0; j < mapSize; ++j)
		{
			InitiateTile(grid[i][j], { i, j }, hge);
		}
	}

}

void Map::Release(HGE* hge)
{
	for (auto& i : grid)
	{
		for (auto& j : i)
		{
			j.Release(hge);
		}
	}

	hge->Texture_Free(tileTexture);
}

void Map::HandleEvent(HGE* hge, hgeInputEvent* inputEvent)
{
	if ((inputEvent->type == INPUT_MBUTTONDOWN) && (inputEvent->key == HGEK_RBUTTON))
	{
		Vector2 point;
		hge->Input_GetMousePos(&point.x, &point.y);

		for (auto& i : grid)
		{
			for (auto& j : i)
			{
				if (j.CheckHit(point))
				{
					j.HandleEvent(hge, inputEvent);
					InformListeners();
				}
			}
		}
	}
}

void Map::Update(float dt)
{
}

void Map::Render(HGE* hge)
{
	Vector2 point;
	hge->Input_GetMousePos(&point.x, &point.y);

	for (auto& i : grid)
	{
		for (auto& j : i)
		{
			if (j.CheckHit(point))
			{
				j.SetSelected();
			}
			else
			{
				j.SetUnselected();
			}
			j.Render(hge);
		}
	}
}

void Map::AddListener(MapListener* listener)
{
	listeners.push_back(listener);
}

void Map::InitiateTile(Tile& tile, const iVector2& index, HGE* hge)
{
	float tileCenterX = 0;
	float tileCenterY = 0;
	int offsetX = 0;
	int offsetY = 0;

	int quadrantX = (index.j / TileInitHelp::halfSize) ? 1 : -1;
	int quadrantY = (index.i / TileInitHelp::halfSize) ? 1 : -1;

	tileCenterX += quadrantX *  tile.Size();
	tileCenterY += quadrantY * tile.Size();

	offsetX = TileInitHelp::QuadrantBasedOffset(index.j);
	offsetY = TileInitHelp::QuadrantBasedOffset(index.i);

	tileCenterX += quadrantX *  offsetX * 2 * tile.Size();
	tileCenterY += quadrantY * offsetY * 2 * tile.Size();

	tile.Initiate(hge, { tileCenterX, tileCenterY, 0 });
	tile.SetTexture(tileTexture);
}

iVector2 Map::GetSelectedTileIndex(const Vector2& point) const
{
	for (int i = 0; i < mapSize; ++i)
	{
		for (int j = 0; j < mapSize; ++j)
		{
			if (grid[i][j].CheckHit(point))
			{
				return{ i, j };
			}
		}
	}

	return{ -1, -1 };
}

Tile& Map::GetTileByIndex(const iVector2& index)
{
	return grid[index.i][index.j];
}

void Map::InformListeners() const
{
	for (auto& i : listeners)
	{
		i->OnMapChanged();
	}
}

