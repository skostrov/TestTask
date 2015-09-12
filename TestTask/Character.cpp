#include "Character.h"
#include "Tile.h"


Character::Character(TraversableMap* grid_, const iVector2& startPos, HTEXTURE texture) : grid(grid_), currentPos(startPos), pather(grid)
{
	quad.blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_ZWRITE;

	quad.tex = texture;

	velocity = { 0, 0 };
}


Character::~Character()
{
}

void Character::Initiate(HGE* hge, const Vector3& center)
{
	imCenter = grid->GetTileByIndex(currentPos).ImCenter();

	quad.v[0] = { imCenter.x - size, imCenter.y - size - texOffset, 0.5f, White, 0, 0 };
	quad.v[1] = { imCenter.x + size, imCenter.y - size - texOffset, 0.5f, White, 1, 0 };
	quad.v[2] = { imCenter.x + size, imCenter.y + size - texOffset, 0.5f, White, 1, 1 };
	quad.v[3] = { imCenter.x - size, imCenter.y + size - texOffset, 0.5f, White, 0, 1 };

	grid->GetTileByIndex(currentPos).SetOccupiedByPlayer();
}

void Character::Release(HGE* hge)
{
	hge->Texture_Free(quad.tex);
}

void Character::HandleEvent(HGE* hge, hgeInputEvent* inputEvent)
{
	if (inputEvent->type == INPUT_MBUTTONDOWN)
	{
		if (inputEvent->key == HGEK_LBUTTON)
		{		
			Vector2 point;
			hge->Input_GetMousePos(&point.x, &point.y);

			iVector2 tileIndex = grid->GetSelectedTileIndex(point);

			if (TestIndexValidity(tileIndex))
			{
				vector<void*> foundPath;
				float pathCost;
				int result = FindPath(tileIndex, foundPath, pathCost);

				if (result == micropather::MicroPather::SOLVED)
				{
					SetFoundPathAsCurrent(foundPath);
				}
			}
		}
		else if (inputEvent->key == HGEK_RBUTTON)
		{
			pather.Reset();

			if (!currentPath.empty())
			{
				iVector2 destinationTile = *(currentPath.rbegin());

				vector<void*> foundPath;
				float pathCost;
				int result = FindPath(destinationTile, foundPath, pathCost);

				if (result == micropather::MicroPather::SOLVED)
				{
					SetFoundPathAsCurrent(foundPath);
				}
				else if ((result == micropather::MicroPather::NO_SOLUTION) || (result == micropather::MicroPather::START_END_SAME))
				{
					currentPath.clear();
					currentPath.push_back(currentPos);
				}
			}

		}
	}
}

void Character::Update(float dt)
{
	if (!currentPath.empty())
	{
		float eps = 0.5f;
		
		grid->GetTileByIndex(currentPos).SetFree();

		currentPos = *currentPath.begin();

		OccupyTile();

		Vector2 tileCenter = grid->GetTileByIndex(currentPos).ImCenter();

		if (EuclideanLength( Vector2 { imCenter.x - tileCenter.x, imCenter.y - tileCenter.y } ) <= eps)
		{
			currentPath.erase(currentPath.begin());

			if (currentPath.empty())
			{
				Stop();
			}
			else
			{
				Vector2 nextTileCenter = grid->GetTileByIndex(*currentPath.begin()).ImCenter();

				SetVelocity( { 5 * (nextTileCenter.x - imCenter.x), 5 * (nextTileCenter.y - imCenter.y) } );
			}
		}

		imCenter.x += velocity.x * dt;
		imCenter.y += velocity.y * dt;
	}
}

void Character::Render(HGE* hge)
{
	quad.v[0] = { imCenter.x - size, imCenter.y - size - texOffset, 0.5f, White, 0, 0 };
	quad.v[1] = { imCenter.x + size, imCenter.y - size - texOffset, 0.5f, White, 1, 0 };
	quad.v[2] = { imCenter.x + size, imCenter.y + size - texOffset, 0.5f, White, 1, 1 };
	quad.v[3] = { imCenter.x - size, imCenter.y + size - texOffset, 0.5f, White, 0, 1 };

	hge->Gfx_RenderQuad(&quad);
}

int Character::FindPath(const iVector2& index, vector<void*>& foundPath, float& pathCost)
{
	void* startNode = GraphFormat::IndexToNode(currentPos);
	void* finishNode = GraphFormat::IndexToNode(index);

	return pather.Solve(startNode, finishNode, &foundPath, &pathCost);
}

void Character::SetFoundPathAsCurrent(const vector<void*>& foundPath)
{
	currentPath.clear();
	currentPath.push_back(currentPos);

	for (const auto& i : foundPath)
	{
		currentPath.push_back(GraphFormat::NodeToIndex(i));
	}
}

void Character::SetVelocity(const Vector2& velocity_)
{
	velocity = { velocity_.x, velocity_.y };
}

void Character::Stop()
{
	velocity = { 0, 0 };
}

void Character::OccupyTile()
{
	grid->GetTileByIndex(currentPos).SetOccupiedByPlayer();
}

