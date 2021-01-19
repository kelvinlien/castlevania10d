#include"Fragment.h"

CFragment::CFragment(float x, float y, float nx, int type):CGameObject()
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
	case 2:
		this->fragmentType = BOSS_DEAD_EFFECT;
		ani = 0;
		break;
	case 3:
		this->fragmentType = BOSS_INJURED_EFFECT;
		ani = 4;
		break;
	default:
		this->fragmentType = WATER_FRAGMENT;
		ani = 6;
		break;
	}
}

void CFragment::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	CGameObject::Update(dt, coObjects);
	vy += FRAGMENT_GRAVITY;

	if (fragmentType != BOSS_DEAD_EFFECT && fragmentType != BOSS_INJURED_EFFECT)
	{
		x += dx;
		y += dy;
	}
}

void CFragment::Render()
{
	animation_set->at(ani)->Render(x, y);
}
CFragment::~CFragment()
{

}