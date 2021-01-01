#pragma once
#include "Enemy.h"
#include "Camera.h"
#include "Define.h"
#include <cmath>


#define BOSS_ANI_IDLE	0
#define BOSS_ANI_FLY	1
#define BOSS_FLY_SPEED_X	0.1f
#define BOSS_FLY_SPEED_Y	0.2f


//BBox
#define BOSS_IDLE_BBOX_WIDTH	32
#define BOSS_IDLE_BBOX_HEIGHT	32
#define BOSS_FLY_BBOX_WIDTH		96
#define BOSS_FLY_BBOX_HEIGHT	46

//State
#define BOSS_STATE_IDLE		0
#define	BOSS_STATE_WAITING	1
#define	BOSS_STATE_FLYING	2
#define BOSS_STATE_DEAD		3

//Time
#define BOSS_WAITING_TIME	1500
#define BOSS_FLYING_TIME	1500

class CBoss :public CEnemy
{
	int ani;
	int percentFlyToSimon;
	int ny;
	//flag variables
	bool isFlying;
	bool isWaiting;
	bool isReverse;
	bool isNearSimon;
	//coordinates
	// coordinates

	int leftBound = 4900 + BOSS_FLY_BBOX_WIDTH; // 4900 is leftbound of camera
	int rightBound = 4900 + SCREEN_WIDTH - BOSS_FLY_BBOX_WIDTH;
	int topBound = 80 + BOSS_FLY_BBOX_HEIGHT; // height of Score Board
	int bottomBound = SCREEN_HEIGHT - 100 - BOSS_FLY_BBOX_HEIGHT; // 80 is height of brick

	//DWORD startFlyTime;
	DWORD startWaitTime;

	//target pos
	D3DXVECTOR2 targetPos;
	D3DXVECTOR2 waitingPos;
	
	//distance 
	float flyDistance = 0.0f;
	float fliedDistance = 0.0f;

public:
	CBoss();
	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void SetAnimation();
	void Fly(D3DXVECTOR2 targetPos);
	void SetTargetPos();
	int RandomPercentFlyToSimon() { return  rand() % 3 + 1 ;} // to decide how many percent Boss can fly to Simon
	void RandomWaitingPos(); //to random waiting pos
	void SetDirect(D3DXVECTOR2 targetPos);
	void SetDirectWhenCollideEdge();
	bool isOutCamera() { return (this->x <= leftBound || this->x >= rightBound || this->y <= topBound || this->y >= bottomBound); }
};

