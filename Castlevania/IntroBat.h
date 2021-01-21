#pragma once
#include "GameObject.h"
#define INTRO_BAT_VX	0.015f
#define INTRO_BAT_VY	0.012f

class CIntroBat: public CGameObject
{

public:
	CIntroBat(float x, float y, int nx);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	~CIntroBat();
};
