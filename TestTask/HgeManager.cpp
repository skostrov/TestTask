#include "HgeManager.h"
#include "TraversableMap.h"
#include "Character.h"
#include "Guard.h"


HgeManager* HgeManager::instance = nullptr;

HgeManager::HgeManager()
{
}


HgeManager::~HgeManager()
{
	for (auto& i : *objects)
	{
		delete i;
	}

	delete objects;

	delete instance;
}

HgeManager* HgeManager::Instance()
{
	if (!instance)
	{
		instance = new HgeManager();

		instance->SetHge(nullptr);
		instance->SetObjects(new list<SceneObject*>());
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

list<SceneObject*>* HgeManager::Objects()
{
	return objects;
}

void HgeManager::SetObjects(list<SceneObject*>* objects_)
{
	objects = objects_;
}

bool HgeManager::FrameFunc()
{
	if (HgeManager::Instance()->Hge()->Input_GetKeyState(HGEK_ESCAPE))
	{
		return true;
	}
	else
	{
		hgeInputEvent* inputEvent = new hgeInputEvent();
		HgeManager::Instance()->Hge()->Input_GetEvent(inputEvent);
		float dt = HgeManager::Instance()->Hge()->Timer_GetDelta();


		for (auto& i : *(HgeManager::Instance()->Objects()))
		{
			i->HandleEvent(HgeManager::Instance()->Hge(), inputEvent);
			i->Update(dt);
		}

		delete inputEvent;

		return false;
	}
}

bool HgeManager::RenderFunc()
{
	HgeManager::Instance()->Hge()->Gfx_BeginScene();
	HgeManager::Instance()->Hge()->Gfx_Clear(0);

	for (auto& i : *(HgeManager::Instance()->Objects()))
	{
		i->Render(HgeManager::Instance()->Hge());
	}

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
	HTEXTURE playerTexture = hge->Texture_Load("greenball.png");
	HTEXTURE guardTexture = hge->Texture_Load("redball.png");

	TraversableMap* gameMap = new TraversableMap();
	Character* player = new Character(gameMap, { 0, 0 }, playerTexture);
	Guard* guard = new Guard(gameMap, { 10, 10 }, guardTexture, GuardRouteType::CIRCLE);
	
	gameMap->AddListener(player);
	gameMap->AddListener(guard);


	gameMap->Initiate(hge, { 0, 0, 0 } );
	player->Initiate(hge, { 0, 0, 0 });
	guard->Initiate(hge, { 0, 0, 0 });

	objects->push_back(gameMap);
	objects->push_back(player);
	objects->push_back(guard);

	hge->System_Start();
}

void HgeManager::ThrowMassage()
{
	MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
}

void HgeManager::Release()
{
	for (auto& i : *objects)
	{
		i->Release(hge);
	}

	hge->System_Shutdown();
	hge->Release();
}

