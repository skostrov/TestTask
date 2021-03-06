#pragma once

#include "Utilities.h"
#include "MapListener.h"
#include "Tile.h"


class Map : public SceneObject
{

public:

	Map(const iVector2& finishPos_, HTEXTURE texture);
	~Map() override;

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	void AddListener(MapListener* listener);
	void RemoveListener(MapListener* listener);

	iVector2 GetSelectedTileIndex(const Vector2& point) const;			// ���������� ������ �����, �� �������
																		// ��������� ������ ���� (point - ����������
																		// �������)

	Tile& GetTileByIndex(const iVector2& index);

	iVector2 GetFinishPos() const;

protected:

	void InitiateTile(Tile& tile, const iVector2& index, HGE* hge);		// ��������������� ������� ��
																		// ������������� ��������� ������
																		// �� ����� (������� ����� 
																		// ���������� ��� �����, �������
																		// ����������� ��� realCenter ����
																		// ��������� ��������, ��������� ��
																		// ������� �����

	HTEXTURE tileTexture;

	Vector2 realCenter;								// �������� ���������� ������ ����� 
													// �� ���������� �������� �������������� ��������,
													// �������� � �������� � ����� ������

	Tile grid[mapSize][mapSize];

	iVector2 finishPos;								

	list<MapListener*> listeners;					// ������, ��������� �� ���������� � ������,
													// ����������� �� ���������� ����� (����������
													// �����������)

	void InformListeners() const;

};

