#pragma once
#include"Enemy.h"
#define PANTHER_ANI_SIT_LEFT	  0
#define PANTHER_ANI_SIT_RIGHT     1
#define PANTHER_ANI_RUN_LEFT	  4
#define PANTHER_ANI_RUN_RIGHT	  5
#define PANTHER_ANI_JUMP_LEFT	  2
#define PANTHER_ANI_JUMP_RIGHT	  3

#define PANTHER_JUMP_SPEED_Y 0.4f
#define PANTHER_RUN_SPEED_WHEN_JUMP 0.2f
#define PANTHER_RUN_SPEED    0.15f

#define PANTHER_LEFT_DISTANCE 96.0f//100.0f
#define PANTHER_RIGHT_DISTANCE 96.0f//200.0f
#define PANTHER_GRAVITY 0.002f

#define PANTHER_BBOX_WIDTH	64
#define PANTHER_BBOX_HEIGHT	32

class CPanther:public CEnemy 
{
	bool isJump;
	bool isRun;
	bool isSit;
	float xJumpRight;
	float xJumpLeft;
	float backupX;
	int jumpCount;

	int ani;

public:
	//CPanther(){}
	CPanther(float x, float y,float xJumpRight,float xJumpLeft, int nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	void Jump();
	void Run();
	void SetAnimation();
	
};

