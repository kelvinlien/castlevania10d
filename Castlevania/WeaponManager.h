#pragma once
#include "Weapon.h"

enum Available
{
	DAGGER,
};

class WeaponManager {
	Available available;
	int amount;
public:
	//getter & setter 
	void setAvailable(Available available) { this->available = available; };
	int getAmount() { return this->amount; };
	virtual CWeapon *createWeapon();
};