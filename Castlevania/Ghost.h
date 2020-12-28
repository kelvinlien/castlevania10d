#pragma once
#include"Enemy.h"
#include <cstdlib>
#include <ctime>
#define GHOST_ANI_LEFT   0
#define GHOST_ANI_RIGHT  1
#define GHOST_ANI_DIE	 2

#define GHOST_STATE_IDLE 10
#define GHOST_STATE_WALK 20
#define ENEMY_STATE_DIE  30

#define GHOST_BBOX_WIDTH	32
#define GHOST_BBOX_HEIGHT	64

#define GHOST_GRAVITY 0.002f
#define GHOST_WALKING_SPEED	 0.15f 

#define GHOST_DIE_TIME 200

class CGhost:public CEnemy
{
	int ani;
	DWORD die_time;
	float xbackup;
	float ybackup;
public:
	CGhost(float x, float y, int nx,int itemType);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void SetState(int state);
	virtual void Respawn();
};

