#pragma once
#include "GameObject.h"
#define HELICOPTER_VX	0.02f

class CHelicopter : public CGameObject
{
public:
	CHelicopter();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	~CHelicopter();
};
