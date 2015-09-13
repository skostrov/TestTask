#pragma once


#include "Utilities.h"
#include "SceneObject.h"
#include "TraversableMap.h"

class Projectile : public SceneObject
{

public:

	Projectile(TraversableMap* grid_, const iVector2& startPos, const iVector2& finishPos, HTEXTURE texture_);
	Projectile(const Projectile& other);
	~Projectile();

	void Initiate(HGE* hge, const Vector3& center) override;

	void HandleEvent(HGE* hge, hgeInputEvent* inputEvent) override;
	void Update(float dt) override;

	void Render(HGE* hge) override;

	void GetNextPos();

	void operator =(const Projectile& other);

	void OccupyTile(const iVector2& index) const;
	void FreeTile(const iVector2& index) const;

	bool IsMoving() const;
	void Move(float dt);

	bool IsDestReached() const;

private:

	const int emission = 1000;
	const float velocity = 20.0f;

	const Vector2 texOffset = { 70, 70 };
	const float subtexSize = 20;

	HTEXTURE texture;
	hgeSprite* sprite;
	hgeParticleSystem* particles;

	TraversableMap* grid;

	Vector2 imCenter;

	iVector2 currentPos;
	iVector2 nextPos;
	iVector2 destinationPos;

};

