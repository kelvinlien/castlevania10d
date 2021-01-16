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
#define SIMON_STATE_HURT			1000			
#define SIMON_STATE_SIT_AFTER_FALL	1100
#define SIMON_STATE_AFTER_HURT		1200	


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
	ATTACK_DOWN_RIGHT
};

class Simon : public CGameObject
{
	CWeapon *subWeapons;
	static Simon * __instance;
	Area *area;
	CGame *game;
	Camera* cam;

	int hearts = 10000;
	int health = SIMON_MAX_HEALTH;

	//time variables
	DWORD startSit;
	DWORD startHurt;
	DWORD startUntouchable;
	DWORD attackTime;
	DWORD buffTime;
	DWORD dieTime;


	//Flag of Simon's state
	bool isJump;
	bool isAttack = false;
	bool isSit = false;
	bool isLevelUp = false;
	bool isUsingSubWeapon = false;
	bool isHurt = false;
	bool isFall = false;
	bool isUntouchable = false;
	bool isDead = false;
	bool isBuff = false;

	//flag is true when simon comes and render portal, back part of the castle  
	bool flag;


	int levelUpTime = SIMON_TIME_LEVEL_UP_WHIP;

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
	
	void SetisBuff() { isBuff = true; buffTime = GetTickCount64();}
	void SetHealth(int _health) { health = _health; }
	int GetHealth() { return health; }

	void SetHearts(int _hearts) {  hearts = _hearts; }
	int GetHearts() { return hearts; }

	void SetSubWeapons(CWeapon* wp) { subWeapons = wp; }
	void ResetSimon();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	static Simon * GetInstance();
};



