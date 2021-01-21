#pragma once
#include"Enemy.h"
#define BAT_ANI_LEFT   0
#define BAT_ANI_RIGHT  1
#define BAT_ANI_DIE	 2

#define BAT_STATE_FLY 20
#define ENEMY_STATE_DIE  30

#define BAT_BBOX_WIDTH	32
#define BAT_BBOX_HEIGHT	32

#define BAT_FLY_SPEED_X	 0.15f 
#define BAT_FLY_SPEED_Y	 0.05f 

#define BAT_SPEED_AMPLITUDE 0.004f


#define BAT_DIE_TIME 200

class CBat :public CEnemy
{
	DWORD die_time;
	float amplitude = BAT_SPEED_AMPLITUDE;
public:
	CBat(float x, float y, int nx, int itemType);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void SetState(int state);
};

#pragma once
