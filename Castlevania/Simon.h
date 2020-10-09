#pragma once
#include "GameObject.h"
#include <map> 


#define SIMON_WALKING_SPEED		0.15f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f


#define SIMON_STATE_IDLE		 100
#define SIMON_STATE_SIT			 200
#define SIMON_STATE_JUMP		 300
#define SIMON_STATE_HIT			 400
#define SIMON_STATE_LEVEL_UP		500
#define SIMON_STATE_WALKING_LEFT	600
#define SIMON_STATE_WALKING_RIGHT	700
#define SIMON_STATE_DIE				800
#define SIMON_STATE_STAND			900


#define SIMON_ANI_IDLE_RIGHT	0
#define SIMON_ANI_IDLE_LEFT		1


#define SIMON_ANI_WALKING_RIGHT 2
#define SIMON_ANI_WALKING_LEFT	3


#define SIMON_ANI_JUMP_DUCK_RIGHT	4
#define SIMON_ANI_JUMP_DUCK_LEFT	5

#define SIMON_ANI_HURTING_RIGHT				10
#define SIMON_ANI_HURTING_LEFT				11

#define SIMON_ANI_STAND_ATTACKING_RIGHT				6
#define SIMON_ANI_STAND_ATTACKING_LEFT				7

#define SIMON_ANI_SIT_ATTACKING_RIGHT				8
#define SIMON_ANI_SIT_ATTACKING_LEFT				9

#define SIMON_ANI_DYING_RIGHT				16
#define SIMON_ANI_DYING_LEFT				17


#define SIMON_BBOX_WIDTH  16
#define SIMON_BBOX_HEIGHT 30
#define SIMON_SIT_BBOX_HEIGHT	23
#define SIMON_TIME_JUMPPING_SIT 10

#define SIMON_TIME_LEVEL_UP_WHIP 1500

class Simon : public CGameObject
{
	int level;
	bool isJump;
	bool isAttack = false;
	bool isSit = false;
	bool isLand = false;
	bool isLevelUp = false;

	float start_x;
	float start_y;

	map<int, int> weapons;


	int levelUpTime = SIMON_TIME_LEVEL_UP_WHIP;

	DWORD jumpTime;
	float bottomOld;
	
public:
	Simon(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void CheckLevelUpState(DWORD dt);
	void SetLevel(int l) { level = l; }
	void SetState(int state);
	bool GetIsJump() { return isJump; }
	void SetIsJump(bool a) { isJump = a; }
	bool GetIsSit() { return isSit; }
	bool IsLevelUp() { return isLevelUp; }

	float GetY() { return this->y; }


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};



