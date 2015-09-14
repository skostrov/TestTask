#include "HgeManager.h"
#include "TraversableMap.h"
#include "Character.h"
#include "Guard.h"
#include "Projectile.h"


HgeManager* HgeManager::instance = nullptr;

HgeManager::HgeManager()
{
}


HgeManager::~HgeManager()
{
	delete game;

	delete instance;
}

HgeManager* HgeManager::Instance()
{
	if (!instance)
	{
		instance = new HgeManager();

		instance->hge = nullptr;
		instance->game = new Game();
	}

	return instance;
}

HGE* HgeManager::Hge()
{
	return hge;
}

void HgeManager::SetHge(HGE* hge_)
{
	hge = hge_;
}

Game* HgeManager::GetGame()
{
	return game;
}

void HgeManager::SetGame(Game* game_)
{
	game = game_;
}

bool HgeManager::FrameFunc()
{
	if (HgeManager::Instance()->hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		return true;
	}
	else
	{
		hgeInputEvent* inputEvent = new hgeInputEvent();
		HgeManager::Instance()->Hge()->Input_GetEvent(inputEvent);
		float dt = HgeManager::Instance()->Hge()->Timer_GetDelta();

		HgeManager::Instance()->game->HandleEvent(HgeManager::Instance()->hge, inputEvent);
		HgeManager::Instance()->game->Update(dt);

		delete inputEvent;

		return false;
	}
}

bool HgeManager::RenderFunc()
{
	HgeManager::Instance()->Hge()->Gfx_BeginScene();
	HgeManager::Instance()->Hge()->Gfx_Clear(0);

	HgeManager::Instance()->game->Render(HgeManager::Instance()->hge);

	HgeManager::Instance()->Hge()->Gfx_EndScene();

	return false;
}

bool HgeManager::Initiate()
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_FRAMEFUNC, &HgeManager::FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, &HgeManager::RenderFunc);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_HIDEMOUSE, false);
	hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);
	hge->System_SetState(HGE_TITLE, "Test task");
	hge->System_SetState(HGE_SCREENWIDTH, 1024);
	hge->System_SetState(HGE_SCREENHEIGHT, 768);

	return hge->System_Initiate();
}

void HgeManager::Start()
{
	game->Initiate(hge, { 0, 0, 0 });

	hge->System_Start();
}

void HgeManager::ThrowMassage()
{
	MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
}

void HgeManager::Release()
{
	game->Release(hge);

	hge->System_Shutdown();
	hge->Release();
}

