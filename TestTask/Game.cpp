#include "Game.h"
#include "TraversableMap.h"
#include "Character.h"
#include "Guard.h"
#include "Projectile.h"
#include "Wall.h"


Game::Game()
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
	Wall* rightWall = new Wall(gameMap, true, safeWallTexture, safeWallTexture);
	Wall* leftWall = new Wall(gameMap, false, safeWallTexture, safeWallTexture);
	Character* player = new Character(gameMap, { 0, 0 }, playerTexture);
	Guard* guardCricle = new Guard(gameMap, { mapSize / 10, mapSize / 10 }, guardTexture, GuardRouteType::CIRCLE);
	Guard* guardLine = new Guard(gameMap, { mapSize / 10, mapSize / 2 }, guardTexture, GuardRouteType::JLINE);
	Projectile* projectile = new Projectile(gameMap, { 0, mapSize / 2 }, { mapSize - 1, mapSize / 2 }, particlesTexture);

	gameMap->AddListener(player);
	gameMap->AddListener(guardCricle);
	gameMap->AddListener(guardLine);

	gameMap->Initiate(hge, { 0, 0, 0 });
	rightWall->Initiate(hge, { 0, 0, 0 });
	leftWall->Initiate(hge, { 0, 0, 0 });
	player->Initiate(hge, { 0, 0, 0 });
	guardCricle->Initiate(hge, { 0, 0, 0 });
	guardLine->Initiate(hge, { 0, 0, 0 });
	projectile->Initiate(hge, { 0, 0, 0 });
	
	
	objects.push_back(gameMap);
	objects.push_back(rightWall);
	objects.push_back(leftWall);
	objects.push_back(player);
	objects.push_back(guardCricle);
	objects.push_back(guardLine);
	objects.push_back(projectile);
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
	for (auto& i : objects)
	{
		i->Render(hge);
	}
}

