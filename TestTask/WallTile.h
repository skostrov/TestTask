#pragma once

#include "Utilities.h"
#include "SceneObject.h"

class WallTile : public SceneObject
{
	
public:

	WallTile();
	~WallTile();

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	float Width() const;
	float Height() const;

	Vector3 RealCenter() const;

	Vector2 ImCenter() const;

	DWORD Color() const;
	void SetColor(DWORD color_);

	void SetTexture(HTEXTURE texture);

	bool IsSafe() const;
	void SetSafe();
	void SetDangerous();

	void SetOrient(bool orient_);
	bool Orient();

private:

	const float width = 16.0f;
	const float height = 32.0f;

	Vector3 realCenter;
	Vector2 imCenter;

	hgeQuad quad;

	DWORD color;

	bool isSafe;

	bool orient;					// флаг для определения ориентации стены в простарнстве
									// (true - вдоль оси Ox (правая)
									// false - вдоль оси Oy (левая))

};

