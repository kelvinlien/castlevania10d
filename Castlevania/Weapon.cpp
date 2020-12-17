#include "Weapon.h"

CWeapon::CWeapon() : CGameObject()
{

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	this->animation_set = animation_sets->Get(WEAPON_ANI_SET_ID);
}
