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

	const float size = 16.0f;				// ѕоловина стороны
											// обрамл€ющего квадрата

	const float texOffset = 10.0f;			// —мещение текстуры относительно
											// центра персонажа

	TraversableMap* grid;
	iVector2 currentPos;					// »ндекс тайла, на котором в данный
											// момент находитс€ персонаж

	micropather::MicroPather* pather;
	vector<iVector2> currentPath;

	Vector2 imCenter;						// Ёкранные координаты центра персонажа
											// после применени€ преобразований

	hgeQuad quad;							// ќбрамл€ющий квадрат

	Vector2 velocity;

};

