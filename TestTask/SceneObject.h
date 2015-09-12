#pragma once

#include "Utilities.h"


class SceneObject
{

public:

	SceneObject();
	virtual ~SceneObject();

	virtual void Initiate(HGE* hge, const Vector3& center ) = 0;
	virtual void Release(HGE* hge) = 0;

	virtual void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) = 0;
	virtual void Update(float dt) = 0;

	virtual void Render(HGE* hge) = 0;

};

