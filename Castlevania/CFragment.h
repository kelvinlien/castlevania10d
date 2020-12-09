#pragma once
#include"GameObject.h"
#define WATER_FRAGMENT_ANI 0
#define RUBBLE_FRAGMENT_ANI 1

#define FRAGMENT_SPEED_X		0.02f
#define FRAGMENT_SPEED_Y		0.2f
#define FRAGMENT_GRAVITY		0.0010f

enum  type
{
	WATER_FRAGMENT,
	RUBBLE_FRAGMENT
};

class Fragment :public CGameObject
{
	type fragmentType;
	int ani;
	DWORD existTime=0;
public:
	Fragment(float x, float  y, float  nx, int type);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	~Fragment();
};

