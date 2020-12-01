#pragma once
#include"Enemy.h"
#define PANTHER_ANI_SIT_LEFT	  0
#define PANTHER_ANI_SIT_RIGHT     1
#define PANTHER_ANI_RUN_LEFT	  2
#define PANTHER_ANI_RUN_RIGHT	  3
#define PANTHER_ANI_JUMP_LEFT	  4
#define PANTHER_ANI_JUMP_RIGHT	  5

#define  PANTHER_JUMP_SPEED_Y 0.5f
#define PANTHER_RUN_SPEED 0.2f

#define PANTHER_LEFT_DISTANCE 100.0f
#define PANTHER_RIGHT_DISTANCE 200.0f
#define PANTHER_GRAVITY 0.002f
class CPanther:public CEnemy 
{
	bool isJump;
	bool isRun;
	bool isSit;
	float distance;
	float xJumpRight;
	float xJumpLeft;
	int jumpCount;

public:
	CPanther(float x, float y,float xJumpRight,float xJumpLeft, int nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	void Jump();
	void Run();
	void SetAnimation();
	
};

