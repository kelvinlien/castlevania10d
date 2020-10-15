#pragma once
#include "Weapon.h"
#include "Dagger.h"


enum Available
{
	DAGGER,
};

class WeaponManager {
	Available available;
	int amount;
public:

	//getter & setter 
	int getAmount() { return this->amount; };
	CWeapon *createWeapon(Available available);
};