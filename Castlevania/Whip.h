#pragma once
#include "Weapon.h"

#define WHIP_TYPE 0

#define WHIP_BBOX_SHORT_WIDTH	24
#define WHIP_BBOX_SHORT_HEIGHT	6

#define WHIP_BBOX_LONG_WIDTH	40
#define WHIP_BBOX_LONG_HEIGHT	6

#define WHIP_FRAME1	0
#define WHIP_FRAME2	1
#define WHIP_FRAME3 2

#define WHIP_STATE_LV1_LEFT	1
#define WHIP_STATE_LV2_LEFT	2
#define WHIP_STATE_LV3_LEFT	3
#define WHIP_STATE_LV1_RIGHT	4
#define WHIP_STATE_LV2_RIGHT	5
#define WHIP_STATE_LV3_RIGHT	6

#define WHIP_ANI_LV1_LEFT	0
#define WHIP_ANI_LV2_LEFT	1
#define WHIP_ANI_LV3_LEFT	2
#define WHIP_ANI_LV1_RIGHT	3
#define WHIP_ANI_LV2_RIGHT	4
#define WHIP_ANI_LV3_RIGHT	5

class CWhip :public CWeapon
{
	int level;
public:
	CWhip();

	void Render();

	//void SetState(int state);

	//void Reset();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

