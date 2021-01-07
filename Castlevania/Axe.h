#pragma once
#include "Weapon.h"
#include "Simon.h"
#include "Camera.h"
#include "Define.h"
#include "Utils.h"
#include "Enemy.h"

#define AXE_BBOX_HEIGHT 28
#define AXE_BBOX_WIDTH 30
#define AXE_VX 0.2f
#define AXE_VY 0.5f
#define STATE_AXE_IDLE	0
#define STATE_AXE_LEFT	1
#define STATE_AXE_RIGHT	2
#define ANI_AXE_LEFT 11
#define ANI_AXE_RIGHT 12
#define AXE_GRAVITY	0.015f

class Axe :public CWeapon
{
	LPANIMATION ani;
public:
	Axe();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void SetAnimation();
	void SetState(int state);
};

