#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include "Animations.h"
#include "Camera.h"
#include "Define.h"
#include "FirePot.h"

#define WEAPON_ANI_SET_ID	11

class CWeapon :public CGameObject
{
protected:
	LPANIMATION_SET ani_set;
public:
	bool available;
	bool isFlying;
	CWeapon();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {};
	virtual void Render() {};
};