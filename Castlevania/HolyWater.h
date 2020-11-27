#pragma once
#pragma once
#include "Weapon.h"
#include "FirePot.h"
#include "Simon.h"
#include "Camera.h"
#include "Define.h"
#include "Utils.h"
#include "Enemy.h"

#define HOLY_WATER_BBOX_HEIGHT 16
#define HOLY_WATER_BBOX_WIDTH 16
#define HOLY_WATER_VX 0.15f
#define HOLY_WATER_VY 0.25f
#define STATE_HOLY_WATER_THROW	1
#define STATE_HOLY_WATER_BREAK	2
#define ANI_HOLY_WATER_LEFT 8
#define ANI_HOLY_WATER_RIGHT 9
#define ANI_HOLY_WATER_USING 10
#define HOLY_WATER_GRAVITY	0.015f
#define BURN_TIME	300

class HolyWater :public CWeapon {
	LPANIMATION ani;
	DWORD startBurnTime;
	bool isBreak;
	bool canBeRender;
public:
	HolyWater();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void SetAnimation();
	void SetState(int state);

	bool IsBreak() { return isBreak; }
};