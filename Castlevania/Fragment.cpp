#include"Fragment.h"

CFragment::CFragment(float x, float y, float nx, int type)
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
		ani = 6;
		break;
	case 1:
		this->fragmentType = RUBBLE_FRAGMENT;
		ani = 5;
		break;
	default:
		this->fragmentType = WATER_FRAGMENT;
		ani = 6;
		break;
	}
}

void CFragment::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (GetTickCount() - existTime > 1100)
		isVanish = true;

	if(isVanish == true)
		return;

	CGameObject::Update(dt, coObjects);
	vy += FRAGMENT_GRAVITY;

	x += dx;
	y += dy;
}

void CFragment::Render()
{
	if (existTime == 0)
		existTime = GetTickCount();
	
	if (isVanish == true)
		return;

	animation_set->at(ani)->Render(x, y);
}
CFragment::~CFragment()
{

}