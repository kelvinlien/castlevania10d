#pragma once	
#include "GameObject.h"	
#include "WeaponManager.h"	
#include "Whip.h"	
#include "Enemy.h"	
#include <map> 	
#include "GameMap.h"	
#include "Utils.h"	
#include "Area.h"	
#include "Camera.h"	
#include <cmath> 
#include "TriggerStair.h"
#define SIMON_AUTO_GO_AHEAD_POSITION_X	1310	
#define SIMON_AUTO_GO_BACK_POSITION_X	1350	
#define SIMON_AUTO_GO_THROUGH_FIRST_DOOR	3180	
#define SIMON_WALKING_SPEED		0.15f 	
// ON STAIR SPEED
#define SIMON_ON_STAIR_SPEED_X		0.035f
#define SIMON_ON_STAIR_SPEED_Y		0.035f
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
#define SIMON_STATE_HURT			1000				
#define SIMON_STATE_SIT_AFTER_FALL	1100	
#define SIMON_STATE_AFTER_HURT		1200		
#define SIMON_STATE_GO_UP_STAIR		2000
#define SIMON_STATE_GO_DOWN_STAIR	2100
#define SIMON_STATE_IDLE_ON_STAIR	2200
#define SIMON_STATE_AUTOWALK_ON_STAIR	2300
#define SIMON_BBOX_WIDTH  60
#define SIMON_BBOX_HEIGHT 63
#define SIMON_SIT_BBOX_HEIGHT	46
#define SIMON_TIME_JUMPPING_SIT 10
#define SIMON_TIME_LEVEL_UP_WHIP 700	
#define SIMON_HURT_TIME	 500	
#define SIMON_SIT_AFTER_FALL_TIME	 250	
#define SIMON_UNTOUCHABLE_TIME	 2000	
#define SIMON_MAX_HEALTH	2	
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
};
class Simon : public CGameObject
{
	int currentFrame;

	CWeapon *subWeapons;
	static Simon * __instance;
	animation ani;
	Area *area;
	CGame *game;
	Camera* cam;
	int doorId;
	int hearts = 5;
	int health = SIMON_MAX_HEALTH;
	//time variables	
	DWORD startSit;
	DWORD startHurt;
	DWORD startUntouchable;
	DWORD attackTime;
	DWORD buffTime;
	DWORD dieTime;
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
	bool isHurt = false;
	bool isFall = false;
	bool isUntouchable = false;
	bool isDead = false;
	bool isBuff = false;
	bool isAutoWalking = false;
	//flag is true when simon comes and render portal, back part of the castle  	
	bool flag;

	//Flag of trigger stair
	bool readyToUpStair;
	bool readyToDownStair;
	bool canGoUpStair;
	bool canGoDownStair;
	bool isOnStair;
	bool isAutoWalkOnStair = false;

	int directionY;
	int stairNx, stairNy;
	DWORD time;

	int levelUpTime = SIMON_TIME_LEVEL_UP_WHIP;
	DWORD startBlinkEffect = 0;


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
	void Hurt();
	void SitAfterFall();
	void StartUntouchable();

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
	bool IsHurt() { return isHurt; }
	bool IsUntouchable() { return isUntouchable; }
	bool IsFlagOn() { return flag; }
	bool IsAutoWalking() { return isAutoWalking; }
	void SetAutoWalking(bool a) { isAutoWalking = a; }
	void SetisBuff() { isBuff = true; buffTime = GetTickCount64();}
	void SetHealth(int _health) { health = _health; }
	int GetHealth() { return health; }
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

	void SetHearts(int _hearts) {  hearts = _hearts; }
	int GetHearts() { return hearts; }

	void SetSubWeapons(CWeapon* wp) { subWeapons = wp; }

	void ResetSimon();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	static Simon * GetInstance();
};
