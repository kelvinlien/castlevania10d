#pragma once
#pragma once

#include "Camera.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Animations.h"

// Zombie
#define BULLET_BBOX_WIDTH			30
#define BULLET_BBOX_HEIGHT			65

#define BULLET_SPEED				0.2f
#define FIRE_BALL_GRAVITY				0.002f

#define BULLET_ANI					6 // set tam la dagger vif chua co ani

class Bullet : public CGameObject
{
	LPANIMATION ani;
	bool isFlying;

public:
	Bullet(int nx);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

