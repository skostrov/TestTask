#include "Game.h"
#include "Wall.h"
#include "Guard.h"
#include "Cannon.h"


Game::Game() : status(GameStatus::INPROCESS)
{
}

Game::~Game()
{
	for (auto& i : objects)
	{
		delete i;
	}
}

void Game::Initiate(HGE* hge, const Vector3& center)
{
	mapTexture = hge->Texture_Load(mapTextureName);
	playerTexture = hge->Texture_Load(playerTextureName);
	guardTexture = hge->Texture_Load(guardTextureName);
	particlesTexture = hge->Texture_Load(particlesTextureName);
	safeWallTexture = hge->Texture_Load(safeWallTextureName);

	TraversableMap* gameMap = new TraversableMap(mapTexture);
	Wall* rightWall = new Wall(gameMap, true, {  }, safeWallTexture, safeWallTexture);
	Wall* leftWall = new Wall(gameMap, false, { mapSize / 2, mapSize / 2 - 1 }, safeWallTexture, safeWallTexture);
	Character* userPlayer = new Character(gameMap, { 0, 0 }, playerTexture);
	Guard* guardCricle = new Guard(gameMap, { mapSize / 10, mapSize / 10 }, guardTexture, GuardRouteType::CIRCLE);
	Guard* guardLine = new Guard(gameMap, { mapSize / 2, mapSize / 10 }, guardTexture, GuardRouteType::ILINE);
	Cannon* cannon = new Cannon(gameMap, { 0, mapSize / 2 }, { mapSize - 1, mapSize / 2 }, 2.0f, particlesTexture);

	gameField = gameMap;
	player = userPlayer;

	gameMap->AddListener(userPlayer);
	gameMap->AddListener(guardCricle);
	gameMap->AddListener(guardLine);

	gameMap->Initiate(hge, { 0, 0, 0 });
	rightWall->Initiate(hge, { 0, 0, 0 });
	leftWall->Initiate(hge, { 0, 0, 0 });
	userPlayer->Initiate(hge, { 0, 0, 0 });
	guardCricle->Initiate(hge, { 0, 0, 0 });
	guardLine->Initiate(hge, { 0, 0, 0 });
	cannon->Initiate(hge, { 0, 0, 0 });
	
	objects.push_back(gameMap);
	objects.push_back(rightWall);
	objects.push_back(leftWall);
	objects.push_back(userPlayer);
	objects.push_back(guardCricle);
	objects.push_back(guardLine);
	objects.push_back(cannon);
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
	for (auto& i : objects)
	{
		i->HandleEvent(hge, inputEvent);
	}
}

void Game::Update(float dt)
{
	for (auto& i : objects)
	{
		i->Update(dt);
	}
}

void Game::Render(HGE* hge)
{
	CheckPlayer();

	for (auto& i : objects)
	{
		i->Render(hge);
	}
}

GameStatus Game::Status()
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
}

