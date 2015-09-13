#pragma once

#include "Utilities.h"
#include "Game.h"


class HgeManager
{

public:

	~HgeManager();

	static HgeManager* Instance();

	HGE* Hge();
	void SetHge(HGE* hge_);

	Game* GetGame();
	void SetGame(Game* game_);

	static bool FrameFunc();
	static bool RenderFunc();

	bool Initiate();
	void Start();
	void ThrowMassage();
	void Release();

private:

	HgeManager();
	HgeManager(const HgeManager& other);
	void operator = (const HgeManager& other);

	static HgeManager* instance;

	HGE* hge;
	Game* game;

};

