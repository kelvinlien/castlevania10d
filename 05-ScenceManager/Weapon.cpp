#include "Weapon.h"

CWeapon::CWeapon() : CGameObject()
{
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	available = false;

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	this->animation_set = animation_sets->Get(WEAPON_ANI_SET_ID);
}
