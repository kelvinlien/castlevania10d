#pragma once
#include "Weapon.h"
#include "Dagger.h"


enum Available
{
	DAGGER,
};

class WeaponManager {

	static WeaponManager * __instance;

	Available available;
	int amount;
public:

	//getter & setter 
	int getAmount() { return this->amount; };
	CWeapon *createWeapon(Available available);
	static WeaponManager * GetInstance();
};