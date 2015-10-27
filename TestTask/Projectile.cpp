#include "Projectile.h"
#include "HgeManager.h"


Projectile::Projectile(TraversableMap* grid_, const iVector2& startPos, const iVector2& finishPos, HTEXTURE texture_) : grid(grid_),
	currentPos(startPos),
	nextPos(startPos),
	destinationPos(finishPos),
	texture(texture_),
	sprite(nullptr),
	particles(nullptr)
{
}

Projectile::Projectile(const Projectile& other)
{
	texture = other.texture;
	grid = other.grid;
	imCenter = other.imCenter;
	currentPos = other.currentPos;
	nextPos = other.nextPos;
	destinationPos = other.destinationPos;
}

Projectile::~Projectile()
{
	delete sprite;
	delete particles;
}

void Projectile::Initiate(HGE* hge, const Vector3& center)
{
	imCenter = grid->GetTileByIndex(currentPos).GetImCenter();

	sprite = new hgeSprite(texture, texOffset.x, texOffset.y, subtexSize, subtexSize);

	sprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD);

	particles = new hgeParticleSystem("particles.psi", sprite);

	particles->info.nEmission = emission;
	particles->info.fParticleLifeMin = 0.15f;
	particles->info.fParticleLifeMax = 0.2f;
	particles->MoveTo(imCenter.x, imCenter.y);
	particles->Fire();

	OccupyTile(currentPos);
	OccupyTile(nextPos);
}

void Projectile::HandleEvent(HGE* hge, hgeInputEvent* inputEvent)
{
}

void Projectile::Update(float dt)
{
	if (IsMoving())
	{
		Move(dt);
		particles->MoveTo(imCenter.x - subtexSize - 10, imCenter.y - subtexSize);
	}
	else
	{
		GetNextPos();
		if (!IsDestReached())
		{
			OccupyTile(nextPos);
		}
		else
		{
			FreeTile(currentPos);
			FreeTile(nextPos);
		}
	}

	particles->Update(dt);
}

void Projectile::Render(HGE* hge)
{
	if (!IsDestReached())
	{
		particles->Render();
	}
}

void Projectile::operator =(const Projectile& other)
{
	texture = other.texture;
	grid = other.grid;
	imCenter = other.imCenter;
	currentPos = other.currentPos;
	nextPos = other.nextPos;
	destinationPos = other.destinationPos;
}

void Projectile::OccupyTile(const iVector2& index) const
{
	grid->GetTileByIndex(index).SetDangerous();
	grid->GetTileByIndex({ index.i, index.j - 1 }).SetDangerous();
}

void Projectile::FreeTile(const iVector2& index) const
{
	grid->GetTileByIndex(index).SetSafe();
	grid->GetTileByIndex({ index.i , index.j - 1 }).SetSafe();
}

void Projectile::GetNextPos()
{
	Vector2 direction = { float(destinationPos.i - currentPos.i), float(destinationPos.j - currentPos.j) };

	Vector2 normalizedDirection = direction / EuclideanLength(direction);

	iVector2 nextMove;
	if (abs(normalizedDirection.x) > abs(normalizedDirection.y))
	{
		nextMove = { 1, 0 };
		nextMove *= Sign(normalizedDirection.x);
	}
	else
	{
		nextMove = { 0, 1 };
		nextMove *= Sign(normalizedDirection.y);
	}

	nextPos += nextMove;
}

bool Projectile::IsMoving() const
{
	return currentPos != nextPos;
}

void Projectile::Move(float dt)
{
	Vector2 direction = grid->GetTileByIndex(nextPos).GetImCenter() - imCenter;
	float dirLength = EuclideanLength(direction);
	Vector2 normalizedDir = direction / dirLength;

	if (dirLength > Eps)
	{
		imCenter += direction * velocity * dt;
	}
	else
	{
		FreeTile(currentPos);
		if (nextPos == destinationPos)
		{
			FreeTile(nextPos);
		}
		currentPos = nextPos;
	}
}

bool Projectile::IsDestReached() const
{
	return currentPos == destinationPos;
}

