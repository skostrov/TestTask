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

	iVector2 CurrentPos();
	iVector2 NextPos();

protected:

	int FindPath(vector<void*>& foundPath);

	const float size = 16.0f;				// ѕоловина стороны
											// обрамл€ющего квадрата

	const float texOffset = 10.0f;			// —мещение текстуры относительно
											// центра персонажа

	const float velocity = 10.0f;			// —корость анимации перехода

	TraversableMap* grid;
	iVector2 currentPos;					// »ндекс тайла, на котором в данный
											// момент находитс€ персонаж

	iVector2 nextPos;						// “айл, в который персонаж переходит
											// в данный момент времени
											// (переход нельз€ прервать изменением
											// направлени€ движени€, анимаци€ перехода
											// непрерывна)

	iVector2 destinationPos;				// “екуща€ точка назначени€ персонажа

	micropather::MicroPather pather;		// —торонний класс, реализующий алгоритм
											// поиска A*

	vector<iVector2> currentPath;

	Vector2 imCenter;						// Ёкранные координаты центра персонажа
											// после применени€ преобразований

	hgeQuad quad;							// ќбрамл€ющий квадрат

};

