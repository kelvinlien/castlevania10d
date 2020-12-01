#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include "Animations.h"

#define WEAPON_ANI_SET_ID	5

class CWeapon :public CGameObject
{
	bool isThrown = false;
public:

	CWeapon();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {};
	virtual void Render() {};

	void SetIsThrown(bool isThrown) { this->isThrown = isThrown; }
	bool GetIsThrown() { return isThrown; }

};