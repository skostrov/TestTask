#pragma once

#include "Utilities.h"
#include "MapListener.h"
#include "Tile.h"


class Map : public SceneObject
{

public:

	Map(const iVector2& finishPos_, HTEXTURE texture);
	~Map() override;

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	void AddListener(MapListener* listener);
	void RemoveListener(MapListener* listener);

	iVector2 GetSelectedTileIndex(const Vector2& point) const;			// Возвращает индекс тайла, на который
																		// указывает курсор мыши (point - координаты
																		// курсора)

	Tile& GetTileByIndex(const iVector2& index);

	iVector2 GetFinishPos() const;

protected:

	void InitiateTile(Tile& tile, const iVector2& index, HGE* hge);		// Вспомогательная функция по
																		// инициализации отдельных тайлов
																		// на карте (каждому тайлу 
																		// передается его центр, который
																		// вычисляется как realCenter плюс
																		// некоторое смещение, зависящее от
																		// индекса тайла

	HTEXTURE tileTexture;

	Vector2 realCenter;								// Экранные координаты центра карты 
													// до применения аффинных преобразований вращения,
													// проекции и смещения в центр экрана

	Tile grid[mapSize][mapSize];

	iVector2 finishPos;								

	list<MapListener*> listeners;					// Список, состоящий из стражников и игрока,
													// подписанных на обновление карты (добавление
													// препятствий)

	void InformListeners() const;

};

