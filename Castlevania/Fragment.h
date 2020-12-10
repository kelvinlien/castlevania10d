#pragma once
#include"GameObject.h"

#define WATER_FRAGMENT_ANI 0
#define RUBBLE_FRAGMENT_ANI 1

#define FRAGMENT_SPEED_X		0.06f
#define FRAGMENT_SPEED_Y		0.07f
#define FRAGMENT_GRAVITY		0.012f

enum  type
{
	WATER_FRAGMENT,
	RUBBLE_FRAGMENT
};

class CFragment :public CGameObject
{
	type fragmentType;
	int ani;
	DWORD existTime = 0;
public:
	CFragment(float x, float  y, float  nx, int type);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Render();
	~CFragment();
};

typedef CFragment * LPFRAGMENT;