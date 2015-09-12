#pragma once

#include "Utilities.h"
#include "SceneObject.h"


class HgeManager
{

public:

	~HgeManager();

	static HgeManager* Instance();

	HGE* Hge();
	void SetHge(HGE* hge_);

	list<SceneObject*>* Objects();
	void SetObjects(list<SceneObject*>* objects_);

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
	list<SceneObject*>* objects;

};

