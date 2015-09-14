#pragma once

#include "Utilities.h"
#include "SceneObject.h"
#include "Character.h"
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
	~Game();

	void Initiate(HGE* hge, const Vector3& center) override;
	void Release(HGE* hge);

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	GameStatus Status();

	void CheckPlayer();

	void DisplayVictory();
	void DisplayDefeat();
	void Restart();

private:

	GameStatus status;

	Character* player;
	TraversableMap* gameField;

	list<SceneObject*> objects;

	const char* mapTextureName = "tile.png";
	const char* safeWallTextureName = "safewall.png";
	const char* playerTextureName = "greenball.png";
	const char* guardTextureName = "redball.png";
	const char* particlesTextureName = "particles.png";

	const char* menuFontName = "font.fnt";

	HTEXTURE mapTexture;
	HTEXTURE safeWallTexture;
	HTEXTURE playerTexture;
	HTEXTURE guardTexture;
	HTEXTURE particlesTexture;

	hgeFont* menuFont;

};

