#pragma once

#include "Utilities.h"
#include "SceneObject.h"
#include "Projectile.h"
#include "TraversableMap.h"


class Cannon : public SceneObject
{

public:

	Cannon(TraversableMap* grid_, const iVector2& position_, const iVector2& firePos_, float fireDelay_, HTEXTURE texture);
	~Cannon() override;

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

private:

	void Fire();						// Добавление новых снарядов в projectiles
										// (за отрисовку и обновление снарядов
										// отвечает пушка)

	void FreeProjectiles();				// Удаление снарядов, достигнувших firePos,
										// из списка projectiles

	HTEXTURE projTexture;				// Текстура частиц снаряда (сама пушка
										// не отрисовывается)

	list<Projectile*> projectiles;

	TraversableMap* grid;

	iVector2 position;					// Индекс тайла, в котором находится пушка

	iVector2 firePos;					// Индекс тайла, в который направляются снаряды

	float fireDelay;
	float accTime;

};

