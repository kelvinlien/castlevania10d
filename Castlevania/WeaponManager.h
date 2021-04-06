#pragma once
#include "Weapon.h"
#include "Dagger.h"
#include "HolyWater.h"
#include "StopWatch.h"
#include "Axe.h"

enum Available
{
	UNKNOWN,
	DAGGER,
	HOLYWATER,
	STOPWATCH,
	AXE
};

class WeaponManager {

	static WeaponManager * __instance;

	Available available;
	int amount;
public:

	//getter & setter
	Available GetAvailable() { return available; }
	int getAmount() { return this->amount; };
	Available getType() { return available; }
	CWeapon *createWeapon(Available available);
	static WeaponManager * GetInstance();
};