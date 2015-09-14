#pragma once

#include "Utilities.h"
#include "SceneObject.h"
#include "Isometric.h"


class Tile : public SceneObject
{

public:

	Tile();
	~Tile() override;

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	bool CheckHit(const Vector2& imPoint) const;

	float GetSize() const;

	Vector2 GetRealCenter() const;

	Vector2 GetImCenter() const;

	DWORD GetColor() const;

	void SetTexture(HTEXTURE texture);

	bool IsSelected() const;
	void SetSelected();
	void SetUnselected();

	bool IsBlocked() const;
	void SetBlock();
	void ReleaseBlock();

	bool IsSafe() const;
	void SetSafe();
	void SetDangerous();

	bool IsOccupiedByPlayer() const;
	void SetOccupiedByPlayer();
	void SetFreeOfPlayer();

	bool IsOccupiedByGuard() const;
	void SetOccupiedByGuard();
	void SetFreeOfGuard();

	bool IsFinish() const;
	void SetFinish();

private:

	void SetColor(DWORD color_);

	const float size = 16.0f;			// �������� ������� �����

	Vector2 realCenter;					// �������� ���������� ������ ����� 
										// �� ���������� �������� �������������� ��������,
										// �������� � �������� � ����� ������

	Vector2 imCenter;					// �������� ���������� ������ �����
										// ����� ���������� ��������������

	hgeQuad quad;						// ���� � �������� ����������� ����� ����������
										// �������������� (����� ����� �����, ������������
										// ��� ���������)

	DWORD color;

	bool isSelected;
	bool isBlocked;
	bool isSafe;
	bool isOccupiedByPlayer;
	bool isOccupiedByGuard;
	bool isFinish;

};

