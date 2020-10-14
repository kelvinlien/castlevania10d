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
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {};
	virtual void Render() {};
};