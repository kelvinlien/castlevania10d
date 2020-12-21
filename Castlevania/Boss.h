#pragma once
#include "Enemy.h"

#define BOSS_ANI_IDLE	0
#define BOSS_ANI_FLY	1
#define BOSS_FLY_SPEED	0.2f
#define BOSS_GRAVITY	0.0015f
#define BOSS_IDLE_BBOX_WIDTH	32
#define BOSS_IDLE_BBOX_HEIGHT	32
#define BOSS_FLY_BBOX_WIDTH	96
#define BOSS_FLY_BBOX_HEIGHT	46

class CBoss :public CEnemy
{
	int ani;
	bool isFly;

public:
	CBoss();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void SetAnimation();
	void Fly();
};

