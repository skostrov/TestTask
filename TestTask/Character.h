#pragma once

#include "Utilities.h"
#include "SceneObject.h"
#include "micropather.h"
#include "TraversableMap.h"


class Character : public SceneObject
{

public:

	Character(TraversableMap* grid_, const iVector2& startPos, HTEXTURE texture);
	virtual ~Character();

	void Initiate(HGE* hge, const Vector3& center) override;
	void Release(HGE* hge) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	int FindPath(const iVector2& index, vector<void*>& foundPath, float& pathCost);

	void SetFoundPathAsCurrent(const vector<void*>& foundPath);

	void SetVelocity(const Vector2& velocity_);
	void Stop();

	virtual void OccupyTile();

protected:

	const float size = 16.0f;				// �������� �������
											// ������������ ��������

	const float texOffset = 10.0f;			// �������� �������� ������������
											// ������ ���������

	TraversableMap* grid;
	iVector2 currentPos;					// ������ �����, �� ������� � ������
											// ������ ��������� ��������

	micropather::MicroPather* pather;
	vector<iVector2> currentPath;

	Vector2 imCenter;						// �������� ���������� ������ ���������
											// ����� ���������� ��������������

	hgeQuad quad;							// ����������� �������

	Vector2 velocity;

};

