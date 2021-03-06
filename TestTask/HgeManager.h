#pragma once

#include "Game.h"


class HgeManager
{

public:

	~HgeManager();

	static HgeManager* Instance();

	HGE* Hge();

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
	hgeFont* gameFont;

	const char* gameFontName = "font1.fnt";

};

