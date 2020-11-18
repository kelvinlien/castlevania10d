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
	static CWhip* __instance;
	float xOffset;
	float yOffset;
public:
	CWhip();
	void SetLevel(int level) { this->level = level; }
	int GetLevel() { return level; }
	void LevelUp();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	/*bool isCollision(RECT r1, RECT r2);*/   //can use this to check collision for whip or only use the code i write in Update
	void SetDirect(int nx) { this->nx = nx; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	static CWhip * GetInstance();
};

