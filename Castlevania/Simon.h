#pragma once
#include "GameObject.h"
#include "WeaponManager.h"
#include "Whip.h"
#include <map> 
#include <cmath> 
#include "TriggerStair.h"


// ON STAIR SPEED
#define SIMON_ON_STAIR_SPEED_X		0.035f
#define SIMON_ON_STAIR_SPEED_Y		0.035f
//
#define SIMON_WALKING_SPEED		0.15f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f


#define SIMON_STATE_IDLE		 100
#define SIMON_STATE_SIT			 200
#define SIMON_STATE_JUMP		 300
#define SIMON_STATE_ATTACK			 400
#define SIMON_STATE_LEVEL_UP		500
#define SIMON_STATE_WALKING_LEFT	600
#define SIMON_STATE_WALKING_RIGHT	700
#define SIMON_STATE_DIE				800
#define SIMON_STATE_STAND			900
#define SIMON_STATE_GO_UP_STAIR		1000
#define SIMON_STATE_GO_DOWN_STAIR	2000
#define SIMON_STATE_IDLE_ON_STAIR	3000
#define SIMON_STATE_AUTOWALK_ON_STAIR	3100
#define SIMON_BBOX_WIDTH  60
#define SIMON_BBOX_HEIGHT 63
#define SIMON_SIT_BBOX_HEIGHT	46
#define SIMON_TIME_JUMPPING_SIT 10

#define SIMON_TIME_LEVEL_UP_WHIP 700

class TriggerStairs;
class Simon : public CGameObject
{
	int currentFrame;

	CWeapon *subWeapons;
	static Simon * __instance;

	int hearts = 5;
	//to handle on stair
	float simonAutoWalkDistance = 0; //to caculate the distance that Simon walked
	float simonAutoWalkDistanceY;
	float autoWalkDistance = 16.0f; //Limit distance that Simon can walk automatic
	float aboveStairOutPoint, belowStairOutPoint;	//variables hold out point
	float backupOnStairX;
	float backupOnStairY;

													//Flag of Simon's state
	bool isJump;
	bool isAttack = false;
	bool isSit = false;
	bool isLand = false;
	bool isLevelUp = false;
	bool isUsingSubWeapon = false;

	//Flag of trigger stair
	bool readyToUpStair;
	bool readyToDownStair;
	bool canGoUpStair;
	bool canGoDownStair;
	bool isOnStair;
	bool isAutoWalkOnStair = false;

	int directionY;
	int stairNx;
	DWORD time;

	int levelUpTime = SIMON_TIME_LEVEL_UP_WHIP;

	DWORD attackTime;

	TriggerStairs *triggerStairs;

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
		ATTACK_DOWN_RIGHT,
		//idle on stair
		IDLE_STAIR_UP_LEFT,
		IDLE_STAIR_UP_RIGHT,
		IDLE_STAIR_DOWN_LEFT,
		IDLE_STAIR_DOWN_RIGHT
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
	void GoUp();
	void GoDown();
	void AutoWalkOnStair();
	void GoUp1Step();
	void GoDown1Step();
	void StopAtFirstStepOnStair();
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
	bool IsReadyToUpStair() { return readyToUpStair; }
	bool IsReadyToDownStair() { return readyToDownStair; }
	bool IsCanGoUpStair() { return canGoUpStair; }
	bool IsCanGoDownStair() { return canGoDownStair; }
	bool IsOnStair() { return isOnStair; }
	void SetReadyToGoStair(int i);
	void SetSimonAutoActionToGoStair(int i);
	bool IsAutoWalkOnStair() { return isAutoWalkOnStair; }
	void SetStairOutPoint(int i);
	float GetAboveStairOutPoint() { return aboveStairOutPoint; }
	float GetBelowStairOutPoint() { return belowStairOutPoint; }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	static Simon * GetInstance();
};
