#pragma once

#include "Utilities.h"
#include "SceneObject.h"
#include "Isometric.h"


class Tile : public SceneObject
{

public:

	Tile();
	~Tile();

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	bool CheckHit(const Vector2& imPoint) const;

	float Size() const;

	Vector2 RealCenter() const;

	Vector2 ImCenter() const;

	DWORD Color() const;
	void SetColor(DWORD color_);

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

private:

	const float size = 16.0f;			// Половина стороны тайла

	Vector2 realCenter;					// Экранные координаты центра тайла 
										// до применения аффинных преобразований вращения,
										// проекции и смещения в центр экрана

	Vector2 imCenter;					// Экранные координаты центра тайла
										// после применения преобразований

	hgeQuad quad;						// Тайл в экранных координатах после применения
										// преобразований (имеет форму ромба, используется
										// при отрисовке)

	DWORD color;

	bool isSelected;
	bool isBlocked;
	bool isSafe;
	bool isOccupiedByPlayer;
	bool isOccupiedByGuard;

};

