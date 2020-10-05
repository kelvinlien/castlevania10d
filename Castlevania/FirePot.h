#pragma once
#include "GameObject.h"

#define	FIREPOT_BBOX_WIDTH 16
#define FIREPOT_BBOX_HEIGHT 32

#define FIREPOT_ANI_1 1
#define FIREPOT_ANI_2 2

class CFirePot :public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CFirePot();
};

