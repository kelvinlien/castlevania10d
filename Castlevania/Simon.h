#pragma once
#include "GameObject.h"
#include "WeaponManager.h"
#include "Whip.h"
#include <map>
#include "GameMap.h"

#define SIMON_AUTO_GO_AHEAD_POSITION_X	1310
#define SIMON_AUTO_GO_BACK_POSITION_X	1350

#define SIMON_WALKING_SPEED		0.15f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.0015f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_AUTO	0
#define SIMON_STATE_IDLE		 100
#define SIMON_STATE_SIT			 200
#define SIMON_STATE_JUMP		 300
#define SIMON_STATE_ATTACK			 400
#define SIMON_STATE_LEVEL_UP		500
#define SIMON_STATE_WALKING_LEFT	600
#define SIMON_STATE_WALKING_RIGHT	700
#define SIMON_STATE_DIE				800
#define SIMON_STATE_STAND			900

#define SIMON_BBOX_WIDTH  60
#define SIMON_BBOX_HEIGHT 63
#define SIMON_SIT_BBOX_HEIGHT	46
#define SIMON_TIME_JUMPPING_SIT 10

#define SIMON_TIME_LEVEL_UP_WHIP 700


class Simon : public CGameObject
{
	CWeapon *subWeapons;
	static Simon * __instance;

	int hearts = 5;

	//Flag of Simon's state
	bool isJump;
	bool isAttack = false;
	bool isSit = false;
	bool isLand = false;
	bool isLevelUp = false;
	bool isUsingSubWeapon = false;

	//flag is true when simon comes and render portal, back part of the castle  
	bool flag;


	int levelUpTime = SIMON_TIME_LEVEL_UP_WHIP;

	DWORD attackTime;


	enum animation
	{
		IDLE_LEFT,
		IDLE_RIGHT,
		WALK_LEFT,
		WALK_RIGHT,
		JUMP_DUCK_LEFT,
		JUMP_DUCK_RIGHT,
		HURT_LEFT,
		HURT_RIGHT,
		DEATH_LEFT,
		DEATH_RIGHT,
		STAIR_UP_LEFT,
		STAIR_UP_RIGHT,
		STAIR_DOWN_LEFT,
		STAIR_DOWN_RIGHT,
		ATTACK_STAND_LEFT,
		ATTACK_STAND_RIGHT,
		ATTACK_DUCK_LEFT,
		ATTACK_DUCK_RIGHT,
		//go up and attack on stair
		ATTACK_UP_LEFT,
		ATTACK_UP_RIGHT,
		//go down and attack on stair
		ATTACK_DOWN_LEFT,
		ATTACK_DOWN_RIGHT
	}ani;

public:

	Simon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);

	//Actions of Simon
	void Attack();
	void Walk();
	void Sit();
	void Jump();
	void Stand();

	//State function
	void CheckLevelUpState(DWORD dt);
	void SetState(int state);

	//Set animation
	void SetAnimation();

	//Getter & setter
	bool IsJump() { return isJump; }
	bool IsSit() { return isSit; }
	bool IsLevelUp() { return isLevelUp; }
	bool IsAttack() { return isAttack; }
	bool IsUsingSubWeapon() { return isUsingSubWeapon; }
	bool IsFlagOn() { return flag; }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	static Simon * GetInstance();
};



