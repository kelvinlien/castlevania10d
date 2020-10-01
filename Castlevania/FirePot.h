#pragma once
#include "Holder.h"

#define	FIREPOT_STATE_IDLE	0
#define FIREPOT_STATE_DIE	100

#define FIREPOT_ANI_IDLE	0
#define FIREPOT_ANI_DIE	1

#define FIREPOT_BBOX_WIDTH	16
#define FIREPOT_BBOX_HEIGHT	32

class CFirePot :public CHolder
{
	float start_x;			
	float start_y;
public:
	CFirePot(float x = 0.0f, float y = 0.0f);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	//CFirePot() {};

	virtual void Render();

	//virtual void SetState(int state);

	//void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

