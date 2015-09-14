#pragma once

#include "Utilities.h"
#include "SceneObject.h"
#include "MapListener.h"
#include "micropather.h"
#include "TraversableMap.h"


class Character : public SceneObject, public MapListener
{

public:

	Character(TraversableMap* grid_, const iVector2& startPos, HTEXTURE texture);
	~Character() override;

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	void OnMapChanged() override;

	bool IsMoving() const;

	iVector2 CurrentPos() const;
	iVector2 NextPos() const;

protected:

	int FindPath(vector<void*>& foundPath);
	void SetFoundPathAsCurrent(const vector<void*>& foundPath);

	void Move(float dt);

	virtual void OccupyTile(const iVector2& index) const;
	virtual void FreeTile(const iVector2& index) const;

	const float size = 16.0f;				// �������� �������
											// ������������ ��������

	const float texOffset = 10.0f;			// �������� �������� ������������
											// ������ ���������

	const float velocity = 10.0f;			// �������� �������� ��������

	TraversableMap* grid;
	iVector2 currentPos;					// ������ �����, �� ������� � ������
											// ������ ��������� ��������

	iVector2 nextPos;						// ����, � ������� �������� ���������
											// � ������ ������ �������
											// (������� ������ �������� ����������
											// ����������� ��������, �������� ��������
											// ����������)

	iVector2 destinationPos;				// ������� ����� ���������� ���������

	micropather::MicroPather pather;		// ��������� �����, ����������� ��������
											// ������ A*

	vector<iVector2> currentPath;

	Vector2 imCenter;						// �������� ���������� ������ ���������
											// ����� ���������� ��������������

	hgeQuad quad;							// ����������� �������

};

