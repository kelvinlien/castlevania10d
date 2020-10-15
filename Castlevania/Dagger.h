#pragma once
#include "Weapon.h"
#include "FirePot.h"
#include "Simon.h"
#define DAGGER_BBOX_HEIGHT 32
#define DAGGER_BBOX_WIDTH 32
#define DAGGER_VX 0.2f


class Dagger :public CWeapon {
	LPANIMATION ani;
public:
	Dagger();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
};