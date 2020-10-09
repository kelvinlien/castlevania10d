#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include "Animations.h"

#define WEAPON_ANI_SET_ID	11

class CWeapon :public CGameObject
{
	float start_x;
	float start_y;

public:
	bool available;

	CWeapon();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) = 0;
	virtual void Render() = 0;
};