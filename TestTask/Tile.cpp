#include "Tile.h"


Tile::Tile() : isSelected(false), isBlocked(false), isSafe(true), isOccupiedByPlayer(false), isOccupiedByGuard(false)
{
	quad.blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_ZWRITE;
}

Tile::~Tile()
{
}

void Tile::Initiate(HGE* hge, const Vector3& center)
{
	realCenter = { center.x, center.y };

	Vector3 imCenter3d = Isometric::Instance()->ToImaginary({ realCenter.x, realCenter.y, 0 });
	imCenter = { imCenter3d.x, imCenter3d.y };

	Vector3 topLeft = Isometric::Instance()->ToImaginary({ realCenter.x - size, realCenter.y - size, 0 });
	Vector3 topRight = Isometric::Instance()->ToImaginary({ realCenter.x + size, realCenter.y - size, 0 });
	Vector3 botRight = Isometric::Instance()->ToImaginary({ realCenter.x + size, realCenter.y + size, 0 });
	Vector3 botLeft = Isometric::Instance()->ToImaginary({ realCenter.x - size, realCenter.y + size, 0 });

	quad.v[0] = { topLeft.x, topLeft.y, 0.5f, White, 0, 0 };
	quad.v[1] = { topRight.x, topRight.y, 0.5f, White, 1, 0 };
	quad.v[2] = { botRight.x, botRight.y, 0.5f, White, 1, 1 };
	quad.v[3] = { botLeft.x, botLeft.y, 0.5f, White, 0, 1 };
}

void Tile::HandleEvent(HGE* hge, hgeInputEvent* inputEvent)
{
	if ((inputEvent->type == INPUT_MBUTTONDOWN) && (inputEvent->key == HGEK_RBUTTON))
	{
		if (isBlocked)
		{
			ReleaseBlock();
		}
		else
		{
			if ((!isOccupiedByPlayer) && (!isOccupiedByGuard))
			{
				SetBlock();
			}
		}
	}
}

void Tile::Update(float dt)
{
}

void Tile::Render(HGE* hge)
{
	hge->Gfx_RenderQuad(&quad);
}

bool Tile::CheckHit(const Vector2& imPoint) const
{
	Vector3 realPoint = Isometric::Instance()->ToReal({ imPoint.x, imPoint.y, 0 });

	return (realPoint.x >= realCenter.x - size) && (realPoint.x <= realCenter.x + size) &&
		(realPoint.y >= realCenter.y - size) && (realPoint.y <= realCenter.y + size);
}

float Tile::Size() const
{
	return size;
}

Vector2 Tile::RealCenter() const
{
	return realCenter;
}

Vector2 Tile::ImCenter() const
{
	return imCenter;
}

DWORD Tile::Color() const
{
	return color;
}

void Tile::SetColor(DWORD color_)
{
	color = color_;

	for (auto& i : quad.v)
	{
		i.col = color_;
	}
}

void Tile::SetTexture(HTEXTURE texture)
{
	quad.tex = texture;
}

bool Tile::IsSelected() const
{
	return isSelected;
}

void Tile::SetSelected()
{
	isSelected = true;

	if (isBlocked)
	{
		SetColor(Orange);
	}
	else
	{
		if ((!isOccupiedByPlayer) && (!isOccupiedByGuard) && isSafe)
		{
			SetColor(Orange);
		}
	}
}

void Tile::SetUnselected()
{
	isSelected = false;

	if (isBlocked)
	{
		SetColor(Black);
	}
	else
	{
		if ((!isOccupiedByPlayer) && (!isOccupiedByGuard) && isSafe)
		{
			SetColor(White);
		}
	}
}

bool Tile::IsBlocked() const
{
	return isBlocked;
}

void Tile::SetBlock()
{
	isBlocked = true;

	SetColor(Black);
}

void Tile::ReleaseBlock()
{
	isBlocked = false;

	SetColor(White);
}

bool Tile::IsSafe() const
{
	return isSafe;
}

void Tile::SetSafe()
{
	isSafe = true;

	SetColor(White);
}

void Tile::SetDangerous()
{
	isSafe = false;

	SetColor(Orange);
}

bool Tile::IsOccupiedByPlayer() const
{
	return isOccupiedByPlayer;
}

void Tile::SetOccupiedByPlayer()
{
	isOccupiedByPlayer = true;

	SetColor(Green);
}

void Tile::SetFreeOfPlayer()
{
	isOccupiedByPlayer = false;

	SetColor(White);
}

bool Tile::IsOccupiedByGuard() const
{
	return isOccupiedByGuard;
}

void Tile::SetOccupiedByGuard()
{
	isOccupiedByGuard = true;

	SetColor(Red);
}

void Tile::SetFreeOfGuard()
{
	isOccupiedByGuard = false;

	SetColor(White);
}

