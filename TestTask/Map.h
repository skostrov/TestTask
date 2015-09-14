#pragma once

#include "Utilities.h"
#include "MapListener.h"
#include "Tile.h"


class Map : public SceneObject
{

public:

	Map(HTEXTURE texture);
	virtual ~Map();

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	void AddListener(MapListener* listener);
	void RemoveListener(MapListener* listener);

	iVector2 GetSelectedTileIndex(const Vector2& point) const;

	Tile& GetTileByIndex(const iVector2& index);

protected:

	void InitiateTile(Tile& tile, const iVector2& index, HGE* hge);

	HTEXTURE tileTexture;

	Vector2 realCenter;								// Ёкранные координаты центра карты 
													// до применени€ аффинных преобразований вращени€,
													// проекции и смещени€ в центр экрана

	Tile grid[mapSize][mapSize];

	list<MapListener*> listeners;

	void InformListeners() const;

};

