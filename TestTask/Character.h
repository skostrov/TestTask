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
	virtual ~Character();

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	void OnMapChanged() override;

	void SetFoundPathAsCurrent(const vector<void*>& foundPath);

	virtual void OccupyTile(const iVector2& index);
	virtual void FreeTile(const iVector2& index);

	bool IsMoving() const;
	void Move(float dt);

protected:

	int FindPath(vector<void*>& foundPath);

	const float size = 16.0f;				// ѕоловина стороны
	// обрамл€ющего квадрата

	const float texOffset = 10.0f;			// —мещение текстуры относительно
	// центра персонажа

	const float velocity = 10.0f;

	TraversableMap* grid;
	iVector2 currentPos;					// »ндекс тайла, на котором в данный
	// момент находитс€ персонаж

	micropather::MicroPather pather;
	vector<iVector2> currentPath;

	Vector2 imCenter;						// Ёкранные координаты центра персонажа
	// после применени€ преобразований

	hgeQuad quad;							// ќбрамл€ющий квадрат

	iVector2 nextPos;
	iVector2 destinationPos;

};

