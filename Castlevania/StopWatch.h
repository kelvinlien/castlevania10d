#pragma once
#include "Weapon.h"
#include "FirePot.h"
#include "Simon.h"
#include "Camera.h"
#include "Define.h"
#include "Utils.h"


class StopWatch :public CWeapon {
	LPANIMATION ani;
public:
	StopWatch();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};
