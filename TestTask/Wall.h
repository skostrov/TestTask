#pragma once

#include "Utilities.h"
#include "WallTile.h"
#include "TraversableMap.h"


class Wall : public SceneObject
{

public:

	Wall(TraversableMap* grid_, bool orient_, vector<int> cannonPos_, HTEXTURE safeTexture_, HTEXTURE dangerousTexture_);
	~Wall() override;

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	Vector3 GetRealCenter() const;

private:

	void InitiateWallTile(int index, HGE* hge);		// Вспомогательная функция по
													// инициализации отдельных тайлов
													// на стене (каждому тайлу 
													// передается его центр, который
													// вычисляется как realCenter плюс
													// некоторое смещение, зависящее от
													// индекса тайла

	HTEXTURE safeTexture;
	HTEXTURE dangerousTexture;

	Vector3 realCenter;								// Экранные координаты центра стены 
													// до применения аффинных преобразований вращения,
													// проекции и смещения в центр экрана

	WallTile* wallGrid[mapSize];

	vector<int> cannonPos;						

	TraversableMap* grid;

	bool orient;									// флаг для определения ориентации стены в простарнстве
													// (true - правая, false - левая)

};

