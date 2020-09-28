#pragma once
#include "GameObject.h"

#define WHIP_BBOX_STATE1_WIDTH	8
#define WHIP_BBOX_STATE1_HEIGHT	32

#define WHIP_BBOX_STATE2_WIDTH	16
#define WHIP_BBOX_STATE2_HEIGHT	24

#define WHIP_BBOX_STATE3_SHORT_WIDTH	24
#define WHIP_BBOX_STATE3_SHORT_HEIGHT	16

#define WHIP_BBOX_STATE3_LONG_WIDTH	40
#define WHIP_BBOX_STATE3_LONG_HEIGHT	16

#define WHIP_STATE_LV1	10
#define WHIP_STATE_LV2	20

#define WHIP_STATE_LV3_CL1	31
#define WHIP_STATE_LV3_CL2	32
#define WHIP_STATE_LV3_CL3	33
#define WHIP_STATE_LV3_CL4	34

#define WHIP_ANI_LV1	0
#define WHIP_ANI_LV2	1

#define WHIP_ANI_LV3_CL1	2
#define WHIP_ANI_LV3_CL2	3
#define WHIP_ANI_LV3_CL3	4
#define WHIP_ANI_LV3_CL4	5

class CWhip :public CGameObject
{
	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	CWhip(float x = 0.0f, float y = 0.0f);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	//CFirePot() {};

	virtual void Render();

	//virtual void SetState(int state);

	//void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

