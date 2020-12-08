#pragma once
#include "Weapon.h"
#include "Dagger.h"
#include "HolyWater.h"
#include "StopWatch.h"


enum Available
{
	DAGGER,
	HOLYWATER,
	STOPWATCH,
};

class WeaponManager {

	static WeaponManager * __instance;

	Available available;
	int amount;
public:

	//getter & setter
	Available GetAvailable() { return available; }
	int getAmount() { return this->amount; };
	CWeapon *createWeapon(Available available);
	static WeaponManager * GetInstance();
};