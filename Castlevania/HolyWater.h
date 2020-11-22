#pragma once
#pragma once
#include "Weapon.h"
#include "FirePot.h"
#include "Simon.h"
#include "Camera.h"
#include "Define.h"
#include "Utils.h"
#define HOLY_WATER_BBOX_HEIGHT 16
#define HOLY_WATER_BBOX_WIDTH 16
#define HOLY_WATER_VX 0.35f
#define HOLY_WATER_VY 0.35f
#define ANI_HOLY_WATER_LEFT 8
#define ANI_HOLY_WATER_RIGHT 9
#define ANI_HOLY_WATER_USING 10



class HolyWater :public CWeapon {
	LPANIMATION ani;
public:
	HolyWater();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void SetAnimation();
};