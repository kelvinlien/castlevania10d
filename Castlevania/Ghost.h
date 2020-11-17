#pragma once
#include"Enemy.h"
#define GHOST_ANI_LEFT   0
#define GHOST_ANI_RIGHT  1

#define GHOST_STATE_IDLE 10
#define GHOST_STATE_WALK 20
#define GHOST_STATE_DIE  30

#define GHOST_BBOX_HEIGHT
#define GHOST_BBOX_WIDTH

#define GHOST_GRAVITY 0.002f
#define GHOST_WALKING_SPEED	0.3f//0.15f 

#define GHOST_BBOX_WIDTH	32
#define GHOST_BBOX_HEIGHT	64
class CGhost:public CEnemy
{
	int ani;
public:
	CGhost(float x, float y, int nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
};

