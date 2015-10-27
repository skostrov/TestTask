#pragma once

#include "Utilities.h"
#include "SceneObject.h"
#include "Guard.h"
#include "TraversableMap.h"


enum class GameStatus
{
	VICTORY,
	GAMEOVER,
	INPROCESS
};

class Game : public SceneObject
{

public:

	Game();
	~Game() override;

	void Initiate(HGE* hge, const Vector3& center) override;
	void Release(HGE* hge);

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	GameStatus Status() const;

	void SetFont(hgeFont* menuFont_);

private:

	void CheckPlayer();
	void CheckGuards();

	void SpawnGuards();

	void DisplayVictory();
	void DisplayDefeat();
	void Restart();

	const iVector2 start = { 0, 0 };
	const iVector2 finish = { mapSize - 1, mapSize - 1 };

	GameStatus status;

	Character* player;
	TraversableMap* gameField;

	list<Guard*> guards;
	list<SceneObject*> objects;

	bool circleGuard;
	bool iLineGuard;
	bool jLineGuard;

	const char* mapTextureName = "tile.png";
	const char* safeWallTextureName = "safewall.png";
	const char* playerTextureName = "greenball.png";
	const char* guardTextureName = "redball.png";
	const char* particlesTextureName = "particles.png";

	HTEXTURE mapTexture;
	HTEXTURE safeWallTexture;
	HTEXTURE playerTexture;
	HTEXTURE guardTexture;
	HTEXTURE particlesTexture;

	hgeFont* menuFont;

};

