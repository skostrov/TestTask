#pragma once

#include "Utilities.h"
#include "SceneObject.h"

class Game : public SceneObject
{

public:

	Game();
	~Game();

	void Initiate(HGE* hge, const Vector3& center) override;
	void Release(HGE* hge) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

private:

	list<SceneObject*> objects;

	const char* mapTextureName = "tile.png";
	const char* playerTextureName = "greenball.png";
	const char* guardTextureName = "redball.png";
	const char* particlesTextureName = "particles.png";

	HTEXTURE mapTexture;
	HTEXTURE playerTexture;
	HTEXTURE guardTexture;
	HTEXTURE particlesTexture;

};

