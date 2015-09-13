#include "WallTile.h"
#include "Isometric.h"


WallTile::WallTile() : isSafe(true)
{
	quad.blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_ZWRITE;
}

WallTile::~WallTile()
{
}

void WallTile::Initiate(HGE* hge, const Vector3& center)
{
	realCenter = center;
	
	Vector3 imCenter3d = Isometric::Instance()->ToImaginary(realCenter);
	imCenter = { imCenter3d.x, imCenter3d.y };

	//int quadrant = orient ? 1 : 0;

	//Vector3 topLeft = Isometric::Instance()->ToImaginary({ realCenter.x - orient * width, realCenter.y - !orient * width, realCenter.z - height });
	//Vector3 topRight = Isometric::Instance()->ToImaginary({ realCenter.x + orient * width, realCenter.y - !orient * width, realCenter.z - height });
	//Vector3 botRight = Isometric::Instance()->ToImaginary({ realCenter.x + orient * width, realCenter.y + !orient * width, realCenter.z + height });
	//Vector3 botLeft = Isometric::Instance()->ToImaginary({ realCenter.x - orient * width, realCenter.y + !orient * width, realCenter.z + height });

	Vector3 topLeft;
	Vector3 topRight;
	Vector3 botRight;
	Vector3 botLeft;

	Vector3 rtopLeft;
	Vector3 rtopRight;
	Vector3 rbotRight;
	Vector3 rbotLeft;

	if (orient)
	{
		rtopLeft = { realCenter.x, realCenter.y - width, realCenter.z - height };
		rtopRight = { realCenter.x, realCenter.y + width, realCenter.z - height };
		rbotRight = { realCenter.x, realCenter.y + width, realCenter.z + height };
		rbotLeft = { realCenter.x, realCenter.y - width, realCenter.z + height };

		topLeft = Isometric::Instance()->ToImaginary({ realCenter.x, realCenter.y - width, realCenter.z - height });
		topRight = Isometric::Instance()->ToImaginary({ realCenter.x, realCenter.y + width, realCenter.z - height });
		botRight = Isometric::Instance()->ToImaginary({ realCenter.x, realCenter.y + width, realCenter.z + height });
		botLeft = Isometric::Instance()->ToImaginary({ realCenter.x, realCenter.y - width, realCenter.z + height });
	}
	else
	{
		rtopLeft = { realCenter.x - width, realCenter.y, realCenter.z - height };
		rtopRight = { realCenter.x + width, realCenter.y, realCenter.z - height };
		rbotRight = { realCenter.x + width, realCenter.y, realCenter.z + height };
		rbotLeft = { realCenter.x - width, realCenter.y, realCenter.z + height };

		topLeft = Isometric::Instance()->ToImaginary({ realCenter.x - width, realCenter.y, realCenter.z - height });
		topRight = Isometric::Instance()->ToImaginary({ realCenter.x + width, realCenter.y, realCenter.z - height });
		botRight = Isometric::Instance()->ToImaginary({ realCenter.x + width, realCenter.y, realCenter.z + height });
		botLeft = Isometric::Instance()->ToImaginary({ realCenter.x - width, realCenter.y, realCenter.z + height });
	}

	quad.v[0] = { topLeft.x, topLeft.y, 0.5f, White, 0, 0 };
	quad.v[1] = { topRight.x, topRight.y, 0.5f, White, 1, 0 };
	quad.v[2] = { botRight.x, botRight.y, 0.5f, White, 1, 1 };
	quad.v[3] = { botLeft.x, botLeft.y, 0.5f, White, 0, 1 };
}

void WallTile::HandleEvent(HGE* hge, hgeInputEvent* inputEvent)
{
}

void WallTile::Update(float dt)
{
}

void WallTile::Render(HGE* hge)
{
	hge->Gfx_RenderQuad(&quad);
}

float WallTile::Width() const
{
	return width;
}

float WallTile::Height() const
{
	return height;
}

Vector3 WallTile::RealCenter() const
{
	return realCenter;
}

Vector2 WallTile::ImCenter() const
{
	return imCenter;
}

DWORD WallTile::Color() const
{
	return color;
}

void WallTile::SetColor(DWORD color_)
{
	color = color_;

	for (auto& i : quad.v)
	{
		i.col = color_;
	}
}

void WallTile::SetTexture(HTEXTURE texture)
{
	quad.tex = texture;
}

bool WallTile::IsSafe() const
{
	return isSafe;
}

void WallTile::SetSafe()
{
	isSafe = true;

	SetColor(White);
}

void WallTile::SetDangerous()
{
	isSafe = false;

	SetColor(Orange);
}

void WallTile::SetOrient(bool orient_)
{
	orient = orient_;
}

bool WallTile::Orient()
{
	return orient;
}

