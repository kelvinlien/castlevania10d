#include "Helicopter.h"

CHelicopter::CHelicopter()
{
	vx = -1 * HELICOPTER_VX;
}
void CHelicopter::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects) {
	CGameObject::Update(dt);
	x += dx;
}

void CHelicopter::Render()
{
	animation_set->at(0)->Render(x, y, 255);
}
