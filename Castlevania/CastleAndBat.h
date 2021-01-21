#pragma once
#include "GameObject.h"
#define CASTLE_AND_BAT_STATE_ACTIVE  0
#define CASTLE_AND_BAT_STATE_IDLE  1

#define CASTLE_AND_BAT_ANI_ACTIVE	0
#define CASTLE_AND_BAT_ANI_IDLE	1

#define CASTLE_AND_BAT_ACTIVE_TIME	1500
 class CastleAndBat :public CGameObject
{
	 DWORD startToRender;
	 bool isIdle = false;
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	CastleAndBat() {
		startToRender = GetTickCount();
	};
};

