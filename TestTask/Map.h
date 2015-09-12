#pragma once

#include "Utilities.h"
#include "SceneObject.h"
#include "Tile.h"


class Map : public SceneObject
{

public:

	Map();
	virtual ~Map();

	void Initiate(HGE* hge, const Vector3& center) override;
	void Release(HGE* hge) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	void InitiateTile(Tile& tile, const iVector2& index, HGE* hge);

	iVector2 GetSelectedTileIndex(const Vector2& point) const;

	Tile& GetTileByIndex(const iVector2& index);

protected:

	const float interTileOffset = 2.0f;				// ������ ����� ������� (������������ ���
													// ��������� ����� ��� �����������
													// ������� ������� ������)

	Vector2 realCenter;								// �������� ���������� ������ ����� 
													// �� ���������� �������� �������������� ��������,
													// �������� � �������� � ����� ������

	Tile grid[mapSize][mapSize];

};
