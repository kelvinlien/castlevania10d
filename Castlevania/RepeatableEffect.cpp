#include "RepeatableEffect.h"

CRepeatableEffect::CRepeatableEffect(float x, float y,type FragmentType):CGameObject()
{
	SetType(x, y, FragmentType);
}
void CRepeatableEffect::SetType(float x,float y, type FragmentType)
{
	this->fragmentType = FragmentType;
	switch (fragmentType)
	{
	case WATER_FRAGMENT:
		fragments.push_back(new CFragment(x - 10, y + 5, -1, WATER_FRAGMENT));
		fragments.push_back(new CFragment(x, y + 2, 0, WATER_FRAGMENT));
		fragments.push_back(new CFragment(x + 10, y + 5, 1, WATER_FRAGMENT));
		break;
	case RUBBLE_FRAGMENT:
		fragments.push_back(new CFragment(x - 10, y + 5, -1, RUBBLE_FRAGMENT));
		fragments.push_back(new CFragment(x + 4, y + 8, 0, RUBBLE_FRAGMENT));
		fragments.push_back(new CFragment(x, y + 1, 1, RUBBLE_FRAGMENT));
		fragments.push_back(new CFragment(x + 15, y + 3, 1, RUBBLE_FRAGMENT));
		break;
	case BOSS_DEAD_EFFECT:
		fragments.push_back(new CFragment(x, y, -1, BOSS_DEAD_EFFECT));
		fragments.push_back(new CFragment(x+20, y, -1, BOSS_DEAD_EFFECT));
		fragments.push_back(new CFragment(x+40, y, -1, BOSS_DEAD_EFFECT));
		fragments.push_back(new CFragment(x, y+25, -1, BOSS_DEAD_EFFECT));
		fragments.push_back(new CFragment(x+20, y+25, -1, BOSS_DEAD_EFFECT));
		fragments.push_back(new CFragment(x+40, y+25, -1, BOSS_DEAD_EFFECT));
		break;
	default:
		break;
	}
}

void CRepeatableEffect::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects )
{
	if (isVanish == true)
		return;

	if (GetTickCount() - existTime > 1300 && existTime != 0)
		isVanish = true;

	for (int i = 0; i < fragments.size(); i++)
		fragments.at(i)->Update(dt, coObjects);
}

void CRepeatableEffect::Render()
{
	if (existTime == 0)
		existTime = GetTickCount();

	if (isVanish == true)
		return;

	for (int i = 0; i < fragments.size(); i++)
		fragments.at(i)->Render();
}

CRepeatableEffect::~CRepeatableEffect()
{
	for (int i = 0; i < fragments.size(); i++)
	{
		delete fragments.at(i);
	}
	fragments.clear();
}