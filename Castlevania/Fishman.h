#pragma once
#include "Enemy.h"
#include "Weapon.h"
#include "Camera.h"
#include "Bullet.h"
// Zombie
#define FISH_MAN_BBOX_WIDTH			28
#define FISH_MAN_BBOX_HEIGHT			64

#define FISH_MAN_WALKING_SPEED		0.1f
#define FISH_MAN_GRAVITY				0.0015f
#define FISH_MAN_JUMPING_SPEED		-0.5f

#define FISH_MAN_WAIT_TO_SHOOT_TIME		3000
#define FISH_MAN_SHOOTING_TIME			700
#define FISH_MAN_DIE_TIME				200


#define FISH_MAN_STATE_DEAD			30
#define FISH_MAN_STATE_SHOOT		1
#define FISH_MAN_STATE_WALK			2
#define FISH_MAN_STATE_JUMP			3


class CFishman : public CEnemy
{	
	//time variables
	DWORD shootingTimePeriod;
	DWORD startShootTime;
	DWORD startWaitToShoot;
	DWORD dieTime;
	
	float randomPosX;
	//flag
	bool isDead = false;
	bool isShoot = false;
	bool isJump = false;
	bool isWalk = false;
	bool isWaitToShoot = false;
	bool canShoot = false;
	bool isShootyet = false;
	CWeapon* bullet = new Bullet();

	enum animation
	{
		FISH_MAN_SHOOT_LEFT,
		FISH_MAN_SHOOT_RIGHT,
		FISH_MAN_WALK_LEFT,
		FISH_MAN_WALK_RIGHT,
		FISH_MAN_IDLE_LEFT,
		FISH_MAN_IDLE_RIGHT,
		FISH_MAN_DIE,

	};
public:

	CFishman(float x, float y, int nx, int itemType);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void SetState(int state);
	//actions
	void Jump() {};
	void WaitToShoot();
};

