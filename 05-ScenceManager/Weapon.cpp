#include "Weapon.h"

CWeapon::CWeapon() : CGameObject()
{
	//SetState(FIREPOT_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	isAvailable = false;
}