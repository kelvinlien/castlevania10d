#include "CFragment.h"

Fragment::Fragment(float x, float y, float nx, int type)
{
	this->x = x;
	this->y = y;
	vx = nx * FRAGMENT_SPEED_X;
	vy = -FRAGMENT_SPEED_Y;
	animation_set = CAnimationSets::GetInstance()->Get(7);
	switch (type)
	{
	case 0:
		this->fragmentType = WATER_FRAGMENT;
		break;
	case 1:
		this->fragmentType = RUBBLE_FRAGMENT;
		ani = 5; 
		break;
	default:
		this->fragmentType = WATER_FRAGMENT;
		break;
	}
}

void Fragment::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt,coObjects);
	vy += FRAGMENT_GRAVITY;

	x += dx;
	y += dy;
}

void Fragment::Render()
{
	animation_set->at(ani)->Render(x,y);
}
