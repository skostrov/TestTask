#include "Character.h"
#include "Tile.h"


Character::Character(TraversableMap* grid_, const iVector2& startPos, HTEXTURE texture) : grid(grid_), currentPos(startPos), nextPos(startPos), destinationPos(startPos), pather(grid)
{
	quad.blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_ZWRITE;

	quad.tex = texture;
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

	OccupyTile(currentPos);
	OccupyTile(nextPos);
}

void Character::HandleEvent(HGE* hge, hgeInputEvent* inputEvent)
{
	if (inputEvent->type == INPUT_MBUTTONDOWN)
	{
		if (inputEvent->key == HGEK_RBUTTON)
		{
			if (!currentPath.empty())
			{
				destinationPos = *currentPath.rbegin();
			}
		}
		else if (inputEvent->key == HGEK_LBUTTON)
		{
			Vector2 point;
			hge->Input_GetMousePos(&point.x, &point.y);

			destinationPos = grid->GetSelectedTileIndex(point);
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

void Character::Update(float dt)
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

void Character::OnMapChanged()
{
	pather.Reset();
}

void Character::SetFoundPathAsCurrent(const vector<void*>& foundPath)
{
	currentPath.clear();

	for (const auto& i : foundPath)
	{
		currentPath.push_back(GraphFormat::NodeToIndex(i));
	}

	currentPath.erase(currentPath.begin());
}

void Character::OccupyTile(const iVector2& index)
{
	grid->GetTileByIndex(index).SetOccupiedByPlayer();
}

void Character::FreeTile(const iVector2& index)
{
	grid->GetTileByIndex(index).SetFreeOfPlayer();
}

bool Character::IsMoving() const
{
	return currentPos != nextPos;
}

void Character::Move(float dt)
{
	Vector2 direction = grid->GetTileByIndex(nextPos).ImCenter() - imCenter;

	if (EuclideanLength(direction) > Eps)
	{
		imCenter += direction * velocity * dt;
	}
	else
	{
		FreeTile(currentPos);
		currentPos = nextPos;
	}
}

int Character::FindPath(vector<void*>& foundPath)
{
	void* startNode = GraphFormat::IndexToNode(nextPos);
	void* finishNode = GraphFormat::IndexToNode(destinationPos);
	float pathCost;

	return pather.Solve(startNode, finishNode, &foundPath, &pathCost);
}

