#pragma once
#include "Weapon.h"

#define WHIP_TYPE 0

#define WHIP_BBOX_STATE1_WIDTH	8
#define WHIP_BBOX_STATE1_HEIGHT	24

#define WHIP_BBOX_STATE2_WIDTH	16
#define WHIP_BBOX_STATE2_HEIGHT	19

#define WHIP_BBOX_STATE3_SHORT_WIDTH	24
#define WHIP_BBOX_STATE3_SHORT_HEIGHT	6

#define WHIP_BBOX_STATE3_LONG_WIDTH	40
#define WHIP_BBOX_STATE3_LONG_HEIGHT	6

#define WHIP_STATE_LV1	1
#define WHIP_STATE_LV2	2
#define WHIP_STATE_LV3	3

#define WHIP_ANI_LV1	0
#define WHIP_ANI_LV2	1
#define WHIP_ANI_LV3	2


class CWhip :public CWeapon
{
	int level;
public:
	CWhip();
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	virtual void Render();

	//virtual void SetState(int state);

	//void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

