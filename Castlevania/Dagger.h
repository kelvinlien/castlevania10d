#pragma once
#include "Weapon.h"
#include "Animations.h"
#include "Simon.h"
#include "FirePot.h"

#define		DAGGER_WIDTH_BBOX  16;
#define		DAGGER_HEIGHT_BBOX  9;
class Dagger :public CWeapon {
public: 
	Dagger(int simonX, int simonY);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects); // for update collision
	void Dagger::GetBoundingBox(float &l, float &t, float &r, float &b);
};