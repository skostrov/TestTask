#include "Cannon.h"
#include "HgeManager.h"


Cannon::Cannon(TraversableMap* grid_, const iVector2& position_, const iVector2& firePos_, float fireDelay_, HTEXTURE texture) : grid(grid_),
	position(position_),
	firePos(firePos_),
	fireDelay(fireDelay_),
	accTime(fireDelay_),
	projTexture(texture)
{
}

Cannon::~Cannon()
{
	for (auto& i : projectiles)
	{
		delete i;
	}
}

void Cannon::Initiate(HGE* hge, const Vector3& center)
{
}

void Cannon::HandleEvent(HGE* hge, hgeInputEvent* inputEvent)
{
}

void Cannon::Update(float dt)
{
	accTime += dt;

	if (accTime >= fireDelay)
	{
		Fire();
		accTime = 0.0f;
	}

	FreeProjectiles();

	for (auto& i : projectiles)
	{
		i->Update(dt);
	}
}

void Cannon::Render(HGE* hge)
{
	for (auto& i : projectiles)
	{
		i->Render(hge);
	}
}

void Cannon::Fire()
{
	projectiles.push_back(new Projectile(grid, position, firePos, projTexture));
	(*projectiles.rbegin())->Initiate(HgeManager::Instance()->Hge(), { 0, 0, 0 });
}

void Cannon::FreeProjectiles()
{
	auto i = projectiles.begin();
	while (i != projectiles.end())
	{
		if ((*i)->IsDestReached())
		{
			i = projectiles.erase(i);
		}
		else
		{
			++i;
		}
	}
}

