#include "WeaponManager.h"

WeaponManager * WeaponManager::__instance = NULL;

WeaponManager *WeaponManager::GetInstance()
{
	if (__instance == NULL) __instance = new WeaponManager();
	return __instance;
}
CWeapon* WeaponManager::createWeapon(Available available) {
	//if (amount < 1) return;
	this->available = available;

	switch (available)
	{
	case DAGGER:
		return new Dagger();
	case HOLYWATER:
		return new HolyWater();
	default:
		break;
	}
}