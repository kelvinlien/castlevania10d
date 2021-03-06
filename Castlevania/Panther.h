#pragma once
#include"Enemy.h"
#include "SmallBrick.h"
#define PANTHER_ANI_SIT_LEFT	  0
#define PANTHER_ANI_SIT_RIGHT     1
#define PANTHER_ANI_RUN_LEFT	  4
#define PANTHER_ANI_RUN_RIGHT	  5
#define PANTHER_ANI_JUMP_LEFT	  2
#define PANTHER_ANI_JUMP_RIGHT	  3
#define PANTHER_ANI_DIE	6

#define PANTHER_JUMP_SPEED_Y 0.4f
#define PANTHER_RUN_SPEED_WHEN_JUMP 0.3f
#define PANTHER_RUN_SPEED    0.15f

#define PANTHER_DISTANCE 158.0f	//from Simon centerX to Panther centerX 
#define PANTHER_GRAVITY 0.002f

#define PANTHER_BBOX_WIDTH	64
#define PANTHER_BBOX_HEIGHT	32

#define PANTHER_STATE_DIE	30
#define PANTHER_STATE_IDLE	31
#define PANTHER_DIE_TIME	200

class CPanther:public CEnemy 
{
	bool isJump;
	bool isRun;
	bool isSit;
	bool isDead;
	float xJumpRight;
	float xJumpLeft;
	int jumpCount;

	DWORD startJumpTime, dieTime;
	float xbackup;
	float ybackup;

public:
	//CPanther(){}
	CPanther(float x, float y, float xJumpLeft, float xJumpRight, int nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void Respawn();
	void Jump();
	void Run();
	void SetAnimation();
	virtual void SetState(int state);
};

