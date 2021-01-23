#include "Enemy.h"
#include "Camera.h"
#include "Define.h"
#include <cmath>

#define BOSS_ANI_IDLE	0
#define BOSS_ANI_FLY	1
#define BOSS_FLY_SPEED_X	0.15f
#define BOSS_FLY_SPEED_Y	0.25f
#define NEAR_DISTANCE_BOSS_AND_SIMON 50.0f
#define TOP_BOUND	120
#define BOT_BOUND	350
#define LEFT_BOUND	4000
#define RIGHT_BOUND	6000



//BBox
#define BOSS_IDLE_BBOX_WIDTH	32
#define BOSS_IDLE_BBOX_HEIGHT	32
#define BOSS_FLY_BBOX_WIDTH		96
#define BOSS_FLY_BBOX_HEIGHT	46

//State
#define BOSS_STATE_IDLE		0
#define	BOSS_STATE_WAITING	1
#define	BOSS_STATE_FLY_TO_TARGET	2
#define BOSS_STATE_FLY_BACK	3
#define BOSS_STATE_FLY_STRAIGHT	4
#define BOSS_STATE_DEAD		5

//Time
#define BOSS_WAITING_TIME	1500
#define	BOSS_STOP_TIME		150

class CBoss :public CEnemy
{
	static CBoss * __instance;
	int percentFlyToSimon;
	int ny;
	int health = 2;

	//flag variables
	bool isFlying;
	bool isWaiting;

	// coordinates
	int leftBound = 4900 + BOSS_FLY_BBOX_WIDTH; // 4900 is leftbound of camera
	int rightBound = 4900 + SCREEN_WIDTH - BOSS_FLY_BBOX_WIDTH;
	int topBound = 120; // height of Score Board
	int bottomBound = SCREEN_HEIGHT - 100 - BOSS_FLY_BBOX_HEIGHT; // 100 is magic number

																  //DWORD startFlyTime;
	DWORD startWaitTime;
	DWORD startStopTime = 0;

	//positions
	D3DXVECTOR2 targetPos;
	D3DXVECTOR2 waitingPos;

	//distance 
	float flyDistance = 0.0f;
	float fliedDistance = 0.0f;

public:
	CBoss();
	static CBoss * GetInstance();
	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void SetAnimation();
	//actions
	void Fly(D3DXVECTOR2 targetPos);
	void FlyBack(D3DXVECTOR2 targetPos);
	void FlyStraight(D3DXVECTOR2 targetPos);
	void SetTargetPos();
	int GetHealthBoss() { return health; }
	int RandomPercentFlyToSimon() { return  rand() % 3 + 1; } // to decide how many percent Boss can fly to Simon
	void RandomWaitingPos(); //to random waiting pos
	void SetDirect(D3DXVECTOR2 targetPos);
	//bool IsOutCamera() { return (this->x <= leftBound || this->x >= rightBound || this->y <= topBound || this->y >= bottomBound); }

};
