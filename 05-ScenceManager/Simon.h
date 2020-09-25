#pragma once
#include "GameObject.h"

#define SIMON_GRAVITY			 0.002f
#define SIMON_JUMP_DEFLECT_SPEED 0.5f

#define SIMON_STATE_IDLE		 2
#define SIMON_STATE_DIE			 3


#define SIMON_ANI_IDLE	 0

class Simon : public CGameObject
{
	int level;
	bool isAttack;
	float start_x;
	float start_y;
public:
	Simon(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetLevel(int l) { level = l; }
	void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};


