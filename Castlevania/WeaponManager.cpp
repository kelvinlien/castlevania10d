#include "WeaponManager.h"

CWeapon* WeaponManager::createWeapon(Available available) {
	//if (amount < 1) return;
	this->available = available;

	switch (available)
	{
	case DAGGER:
		return new Dagger();
	default:
		break;
	}
}