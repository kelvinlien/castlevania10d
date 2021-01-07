#pragma once
#include "Weapon.h"
#include "FirePot.h"
#include "Simon.h"
#include "Boss.h"
#include "Camera.h"
#include "Define.h"
#include "Utils.h"
#define DAGGER_BBOX_HEIGHT 16
#define DAGGER_BBOX_WIDTH 32
#define DAGGER_VX 0.35f
#define ANI_DAGGER_LEFT 6
#define ANI_DAGGER_RIGHT 7


class Dagger :public CWeapon {
	LPANIMATION ani;
public:
	Dagger();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void SetAnimation();
};