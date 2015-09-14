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

	const float width = 16.0f;
	const float height = 32.0f;

	Vector3 realCenter;
	Vector2 imCenter;

	hgeQuad quad;

	DWORD color;

	bool isSafe;

	bool orient;					// флаг для определения ориентации стены в простарнстве
									// (true - правая, false - левая)

};

