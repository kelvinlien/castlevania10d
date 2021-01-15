#include "IntroBat.h"

CIntroBat::CIntroBat(float x, float y, int nx)
{
	this->nx = nx;
	vx = INTRO_BAT_VX * nx;
	vy = INTRO_BAT_VY * -1;
}
void CIntroBat::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects){
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void CIntroBat::Render()
{
	animation_set->at(0)->Render(x,y,255);
}
