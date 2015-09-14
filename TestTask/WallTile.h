#pragma once

#include "Utilities.h"
#include "SceneObject.h"

class WallTile : public SceneObject
{
	
public:

	WallTile();
	~WallTile() override;

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	float GetWidth() const;
	float GetHeight() const;

	Vector3 GetRealCenter() const;

	Vector2 GetImCenter() const;

	DWORD GetColor() const;

	void SetTexture(HTEXTURE texture);

	bool IsSafe() const;
	void SetSafe();
	void SetDangerous();

	void SetOrient(bool orient_);
	bool GetOrient() const;

private:

	void SetColor(DWORD color_);

	const float width = 16.0f;			// Половина ширины тайла
	const float height = 32.0f;			// Половина высоты тайла

	Vector3 realCenter;					// Экранные координаты центра тайла 
										// до применения аффинных преобразований вращения,
										// проекции и смещения в центр экрана

	Vector2 imCenter;					// Экранные координаты центра тайла
										// после применения преобразований

	hgeQuad quad;						// Тайл в экранных координатах после применения
										// преобразований (имеет форму ромба, используется
										// при отрисовке)

	DWORD color;

	bool isSafe;

	bool orient;						// флаг для определения ориентации стены в простарнстве
										// (true - правая, false - левая)

};

