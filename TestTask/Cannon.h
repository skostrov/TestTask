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

	void Fire();						// ���������� ����� �������� � projectiles
										// (�� ��������� � ���������� ��������
										// �������� �����)

	void FreeProjectiles();				// �������� ��������, ������������ firePos,
										// �� ������ projectiles

	HTEXTURE projTexture;				// �������� ������ ������� (���� �����
										// �� ��������������)

	list<Projectile*> projectiles;

	TraversableMap* grid;

	iVector2 position;					// ������ �����, � ������� ��������� �����

	iVector2 firePos;					// ������ �����, � ������� ������������ �������

	float fireDelay;
	float accTime;

};

