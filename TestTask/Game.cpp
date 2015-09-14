#include "Game.h"
#include "Wall.h"
#include "Guard.h"
#include "Cannon.h"
#include "HgeManager.h"


Game::Game() : status(GameStatus::INPROCESS),
	circleGuard(false),
	iLineGuard(false),
	jLineGuard(false)
{
}

Game::~Game()
{
	for (auto& i : guards)
	{
		delete i;
	}

	guards.clear();

	for (auto& i = objects.rbegin(); i != objects.rend(); ++i)
	{
		delete *i;
	}

	objects.clear();
}

void Game::Initiate(HGE* hge, const Vector3& center)
{
	mapTexture = hge->Texture_Load(mapTextureName);
	playerTexture = hge->Texture_Load(playerTextureName);
	guardTexture = hge->Texture_Load(guardTextureName);
	particlesTexture = hge->Texture_Load(particlesTextureName);
	safeWallTexture = hge->Texture_Load(safeWallTextureName);

	TraversableMap* gameMap = new TraversableMap(finish, mapTexture);
	Wall* rightWall = new Wall(gameMap, true, {  }, safeWallTexture, safeWallTexture);
	Wall* leftWall = new Wall(gameMap, false, { mapSize / 3, mapSize / 3 - 1, mapSize * 2 / 3, mapSize * 2 / 3 + 1 }, safeWallTexture, safeWallTexture);
	Character* userPlayer = new Character(gameMap, start, playerTexture);
	Cannon* cannon = new Cannon(gameMap, { 0, mapSize / 3 }, { mapSize - 1, mapSize / 3 }, 4.0f, particlesTexture);
	Cannon* cannon2 = new Cannon(gameMap, { 0, mapSize * 2 / 3 + 1 }, { mapSize - 1, mapSize * 2 / 3 + 1 }, 5.5f, particlesTexture);

	gameField = gameMap;
	player = userPlayer;

	gameMap->AddListener(userPlayer);

	gameMap->Initiate(hge, { 0, 0, 0 });
	rightWall->Initiate(hge, { 0, 0, 0 });
	leftWall->Initiate(hge, { 0, 0, 0 });
	userPlayer->Initiate(hge, { 0, 0, 0 });
	cannon->Initiate(hge, { 0, 0, 0 });
	cannon2->Initiate(hge, { 0, 0, 0 });
	
	objects.push_back(gameMap);
	objects.push_back(rightWall);
	objects.push_back(leftWall);
	objects.push_back(userPlayer);
	objects.push_back(cannon);
	objects.push_back(cannon2);

	circleGuard = false;
	iLineGuard = false;
	jLineGuard = false;
}

void Game::Release(HGE* hge)
{
	hge->Target_Free(mapTexture);
	hge->Target_Free(playerTexture);
	hge->Target_Free(guardTexture);
	hge->Target_Free(particlesTexture);
}

void Game::HandleEvent(HGE* hge, hgeInputEvent* inputEvent)
{
	switch (status)
	{

	case GameStatus::VICTORY:

	case GameStatus::GAMEOVER:

		if (inputEvent->type == INPUT_KEYDOWN || inputEvent->type == INPUT_MBUTTONDOWN)
		{
			Restart();
			status = GameStatus::INPROCESS;
		}

		break;

	case GameStatus::INPROCESS:

		for (auto& i : objects)
		{
			i->HandleEvent(hge, inputEvent);
		}

		for (auto& i : guards)
		{
			i->HandleEvent(hge, inputEvent);
		}

		break;

	}
}

void Game::Update(float dt)
{
	if (status == GameStatus::INPROCESS)
	{
		CheckPlayer();
		CheckGuards();

		SpawnGuards();

		for (auto& i : objects)
		{
			i->Update(dt);
		}

		for (auto& i : guards)
		{
			i->Update(dt);
		}
	}
	
}

void Game::Render(HGE* hge)
{
	switch (status)
	{

	case GameStatus::VICTORY:

		DisplayVictory();

		break;

	case GameStatus::GAMEOVER:

		DisplayDefeat();

		break;

	case GameStatus::INPROCESS:

		for (auto& i : objects)
		{
			i->Render(hge);
		}

		for (auto& i : guards)
		{
			i->Render(hge);
		}

		break;

	}
}

GameStatus Game::Status() const
{
	return status;
}

void Game::CheckPlayer()
{
	iVector2 playerCurPos = player->CurrentPos();
	iVector2 playerNextPos = player->NextPos();

	if (!gameField->GetTileByIndex(playerCurPos).IsSafe() ||
		gameField->GetTileByIndex(playerCurPos).IsOccupiedByGuard() ||
		!gameField->GetTileByIndex(playerNextPos).IsSafe() ||
		gameField->GetTileByIndex(playerNextPos).IsOccupiedByGuard())
	{
		status = GameStatus::GAMEOVER;
	}
	else
	{
		if (playerCurPos == gameField->GetFinishPos())
		{
			status = GameStatus::VICTORY;
		}
	}
}

void Game::CheckGuards()
{
	auto i = guards.begin();
	while (i != guards.end())
	{
		iVector2 guardCurPos = (*i)->CurrentPos();
		iVector2 guardNextPos = (*i)->NextPos();

		if (!gameField->GetTileByIndex(guardCurPos).IsSafe() ||
			!gameField->GetTileByIndex(guardNextPos).IsSafe())
		{

			switch ((*i)->GetRouteType())
			{
				
			case GuardRouteType::CIRCLE:

				circleGuard = false;

				break;

			case GuardRouteType::ILINE:

				iLineGuard = false;

				break;

			case GuardRouteType::JLINE:

				jLineGuard = false;

				break;

			}

			gameField->RemoveListener(*i);
			delete *i;
			i = guards.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void Game::SpawnGuards()
{
	if (!circleGuard)
	{
		Guard* newGuard = new Guard(gameField, { mapSize / 10, mapSize / 10 }, guardTexture, GuardRouteType::CIRCLE);
		circleGuard = true;

		newGuard->Initiate(HgeManager::Instance()->Hge(), { 0, 0, 0 });
		guards.push_back(newGuard);
		gameField->AddListener(newGuard);
	}

	if (!iLineGuard)
	{
		Guard* newGuard = new Guard(gameField, { mapSize / 2, mapSize / 10 }, guardTexture, GuardRouteType::ILINE);
		iLineGuard = true;

		newGuard->Initiate(HgeManager::Instance()->Hge(), { 0, 0, 0 });
		guards.push_back(newGuard);
		gameField->AddListener(newGuard);
	}

	if (!jLineGuard)
	{
		Guard* newGuard = new Guard(gameField, { mapSize / 10, mapSize / 2 }, guardTexture, GuardRouteType::JLINE);
		jLineGuard = true;

		newGuard->Initiate(HgeManager::Instance()->Hge(), { 0, 0, 0 });
		guards.push_back(newGuard);
		gameField->AddListener(newGuard);
	}

	
}

void Game::DisplayVictory()
{
	HgeManager::Instance()->Hge()->Gfx_BeginScene();
	HgeManager::Instance()->Hge()->Gfx_Clear(Black);

	menuFont->SetColor(White);
	menuFont->printf(512, 384, HGETEXT_CENTER, "VICTORY");

	HgeManager::Instance()->Hge()->Gfx_EndScene();
}

void Game::DisplayDefeat()
{
	HgeManager::Instance()->Hge()->Gfx_BeginScene();
	HgeManager::Instance()->Hge()->Gfx_Clear(Black);

	menuFont->SetColor(White);
	menuFont->printf(512, 384, HGETEXT_CENTER, "GAME OVER");

	HgeManager::Instance()->Hge()->Gfx_EndScene();
}

void Game::Restart()
{
	for (auto& i : guards)
	{
		delete i;
	}

	guards.clear();

	for (auto& i = objects.rbegin(); i != objects.rend(); ++i)
	{
		delete *i;
	}

	objects.clear();

	Initiate(HgeManager::Instance()->Hge(), { 0, 0, 0 });
}

void Game::SetFont(hgeFont* menuFont_)
{
	menuFont = menuFont_;
}

